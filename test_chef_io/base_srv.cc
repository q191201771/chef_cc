#include "io_tcp.h"
#include "async_log.h"
#include "task_thread.h"
#include "config.h"
#include "daemon.h"
#include "current_proc.h"
#include <boost/atomic.hpp>
#include <boost/bind.hpp>

using namespace boost;
using namespace chef;

class base_server {
public:
    base_server(std::string local_ip, uint16_t local_port, int16_t thread_num)
        : local_ip_(local_ip)
        , local_port_(local_port)
        , thread_num_(thread_num)
        , io_tcp_(NULL)
        , client_num_(0) {
        chef::async_log::get_mutable_instance().init(chef::async_log::debug, false);
    }
    ~base_server() {
    }

    int run() {
        io_tcp_ = io_tcp::create(local_ip_.c_str(), local_port_, thread_num_,
                boost::bind(&base_server::accept_cb, this, _1, _2, _3),
                boost::bind(&base_server::connect_cb, this, _1, _2),
                boost::bind(&base_server::read_cb, this, _1, _2, _3),
                boost::bind(&base_server::close_cb, this, _1),
                boost::bind(&base_server::error_cb, this, _1, _2),
                boost::bind(&base_server::write_cb, this, _1, _2, _3));
        if (!io_tcp_) {
            CHEF_TRACE_INFO("    :io_tcp::create fail.");
            return -1;
        }
        io_tcp_->run();
        CHEF_TRACE_INFO("    :>base_server::run().");
        return 0;
    }

private:

    void accept_cb(cio_conn_t cc, const char *peer_ip, uint16_t peer_port) {
        CHEF_TRACE_INFO("    :accept_cb(),thread_id=%u,conn_id=%lu,ip=%s,port=%u.",
            cc.thread_index_, cc.conn_id_, peer_ip, peer_port);
        CHEF_TRACE_INFO("    :client num=%lu", ++client_num_);
        cc.arg_ = NULL;
        io_tcp_->set_user_arg(cc);
        io_tcp_->enable_read(cc);
    }
    void connect_cb(cio_conn_t cc, connect_status cs) {
    }
    void read_cb(cio_conn_t cc, void *buf, uint32_t len) {
        CHEF_TRACE_INFO("    :read_cb(),thread_id=%u,conn_id=%lu,len=%u.",
                cc.thread_index_, cc.conn_id_, len);
        //echo
        //io_tcp_->write(cc, buf, len);
    }
    void close_cb(cio_conn_t cc) {
        CHEF_TRACE_INFO("    :close_cb(),thread_id=%u,conn_id=%lu.",
                cc.thread_index_, cc.conn_id_);
        CHEF_TRACE_INFO("    :client num:%lu", --client_num_);
    }
    void error_cb(cio_conn_t cc, uint8_t error_no) {
        CHEF_TRACE_INFO("    :error_cb(),thread_id=%u,conn_id=%lu.",
                cc.thread_index_, cc.conn_id_);
        io_tcp_->close(cc);
    }
    void write_cb(cio_conn_t cc, uint64_t succ_wrote, uint64_t pending_len) {
        CHEF_TRACE_INFO("    :write_cb(),thread_id=%u,conn_id=%lu,succ=%lu,pending=%lu.", 
                cc.thread_index_, cc.conn_id_, succ_wrote, pending_len);
    }

private:
    std::string local_ip_;
    uint16_t local_port_;
    int16_t thread_num_;
    io_tcp_ptr io_tcp_;
    atomic<uint64_t> client_num_;
};

int main(int argc, char **argv)
{
    /// *configuration from config file
    ///  cfg file & exe must @ same dir
    static const char cfg_file[] = "cfg.base_srv";
    std::string cfg_file_with_path = chef::current_proc::obtain_bin_dir() + cfg_file;
    chef::config cfg;
    if (cfg.load(cfg_file_with_path) == -1) {
        fprintf(stderr, "load %s fail.\n", cfg_file_with_path.c_str());
        return -1;
    }
    std::string ip_str;
    std::string port_str;
    std::string thread_num_str;
    std::string daemon_str; /// "true" or "false"
    if (cfg.get("ip", ip_str) == -1 || cfg.get("port", port_str) == -1 
            || cfg.get("thread_num", thread_num_str) == -1
            || cfg.get("daemon", daemon_str) == -1 
            || (daemon_str != "true" && daemon_str != "false")) {
        fprintf(stderr, "get key in %s fail,need key [ip:string] [port:int] [daemon:true/false].\n", 
                cfg_file);
        return -1;
    }

    /// *if daemon
    if (daemon_str == "true") {
    static const char pid_file[] = "pid.base_srv";
    std::string pid_file_with_path = chef::current_proc::obtain_bin_dir() + pid_file;
        if (chef::daemon_init(pid_file_with_path.c_str()) == -1) {
            fprintf(stderr, "chef::daemon::init(%s) fail.\n", pid_file);
            return -1;
        }
    }

    /// *go
    base_server bs(ip_str, atoi(port_str.c_str()), atoi(thread_num_str.c_str()));
    bs.run();

    return 0;
}


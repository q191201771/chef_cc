#include "io_tcp.h"
#include "chef_async_log.h"
#include "chef_task_thread.h"
#include "chef_config.h"
#include "chef_daemon.h"
#include "chef_current_proc.h"
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
        , serviced_num_(0) {
        chef::async_log::get_mutable_instance().init(chef::async_log::info, true);
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
        cc.arg_ = NULL;
        io_tcp_->set_user_arg(cc);
        io_tcp_->enable_read(cc);
    }
    void connect_cb(cio_conn_t cc, connect_status cs) {
    }
    void read_cb(cio_conn_t cc, void *buf, uint32_t len) {
        assert(len == 1 && *((char *)buf) == 'z');
        io_tcp_->write(cc, (void *)"ok", 2);
    }
    void close_cb(cio_conn_t cc) {
        if (++serviced_num_ == 1000) {
            CHEF_TRACE_INFO("serviced_num_=%lu.", (uint64_t)serviced_num_);
        }
    }
    void error_cb(cio_conn_t cc, uint8_t error_no) {
        io_tcp_->close(cc);
    }
    void write_cb(cio_conn_t cc, uint64_t succ_wrote, uint64_t pending_len) {
    }

private:
    std::string local_ip_;
    uint16_t local_port_;
    int16_t thread_num_;
    io_tcp_ptr io_tcp_;
    atomic<uint64_t> serviced_num_;
};

int main(int argc, char **argv)
{
    /// *configuration from config file
    ///  cfg file & exe must @ same dir
    static const char cfg_file[] = "cfg.qps_srv";
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
    static const char pid_file[] = "pid.qps_srv";
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


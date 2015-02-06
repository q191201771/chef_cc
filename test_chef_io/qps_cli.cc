#include "io_tcp.h"
#include "chef_async_log.h"
#include "chef_task_thread.h"
#include "chef_config.h"
#include "chef_daemon.h"
#include "chef_current_proc.h"
#include "chef_buffer.h"
#include <boost/atomic.hpp>
#include <boost/bind.hpp>

using namespace boost;
using namespace chef;

struct client {
    cio_conn_t cc_;
    buffer i_buf_;
};

class client_manager {
public:
    client_manager(std::string peer_ip, uint16_t peer_port, uint32_t connection_num, int16_t thread_num)
        : local_ip_("0.0.0.0")
        , peer_ip_(peer_ip)
        , peer_port_(peer_port)
        , connection_num_(connection_num)
        , thread_num_(thread_num)
        , io_tcp_(NULL)
        , closed_num_(0) {
        chef::async_log::get_mutable_instance().init(chef::async_log::debug, true);
    }
    ~client_manager() {
    }

    int run() {
        io_tcp_ = io_tcp::create(local_ip_.c_str(), -1, thread_num_,
                boost::bind(&client_manager::accept_cb, this, _1, _2, _3),
                boost::bind(&client_manager::connect_cb, this, _1, _2),
                boost::bind(&client_manager::read_cb, this, _1, _2, _3),
                boost::bind(&client_manager::close_cb, this, _1),
                boost::bind(&client_manager::error_cb, this, _1, _2),
                boost::bind(&client_manager::write_cb, this, _1, _2, _3));
        if (!io_tcp_) {
            assert(0);
        }
        for (uint32_t i = 0; i < connection_num_; ++i) {
            client *c = new client();
            io_tcp_->connect(peer_ip_.c_str(), peer_port_, c);
        }

        io_tcp_->run();
        return 0;
    }

private:

    void accept_cb(cio_conn_t cc, const char *peer_ip, uint16_t peer_port) {
        assert(0);
    }
    void connect_cb(cio_conn_t cc, connect_status cs) {
        if (cs == connect_status::connected) {
            io_tcp_->write(cc, (void *)"z", 1);
        }
    }
    void read_cb(cio_conn_t cc, void *buf, uint32_t len) {
        client *c = (client *)(cc.arg_);
        c->i_buf_.append((char *)buf, len);
        if (c->i_buf_.readable() == 2) {
            io_tcp_->close(cc);
        }
    }
    void close_cb(cio_conn_t cc) {
        client *c = (client *)(cc.arg_);
        delete c;
        if (++closed_num_ == connection_num_) {
            io_tcp_->shutdown();
        }
    }
    void error_cb(cio_conn_t cc, uint8_t error_no) {
        assert(0);
        io_tcp_->close(cc);
    }
    void write_cb(cio_conn_t cc, uint64_t succ_wrote, uint64_t pending_len) {
    }

private:
    std::string local_ip_;
    std::string peer_ip_;
    uint16_t peer_port_;
    const uint32_t connection_num_;
    int16_t thread_num_;
    io_tcp_ptr io_tcp_;
    atomic<uint64_t> closed_num_;
};

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "usage: %s <ip> <port> <connections>\n", argv[0]);
        return -1;
    }

    /// *go
    client_manager cm(argv[1], atoi(argv[2]), atoi(argv[3]), 1);
    cm.run();

    return 0;
}


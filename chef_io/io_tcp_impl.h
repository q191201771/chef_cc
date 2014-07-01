#ifndef _CHEF_CHEF_IO_IO_TCP_IMPL_H_
#define _CHEF_CHEF_IO_IO_TCP_IMPL_H_

#include "io_tcp.h"
#include "event_loop.h"
#include <string>
#include <vector>
#include <boost/atomic.hpp>
#include <boost/thread.hpp>

using namespace chef;

class event_loop;

class io_tcp_impl : public boost::noncopyable
{
public:
    io_tcp_impl();
    ~io_tcp_impl();
    int init(const char *ip, int16_t port, uint16_t thread_num,
             const accept_cb_t &acb,
             const connect_cb_t &connect_cb,
             const read_cb_t &rcb,
             const close_cb_t &close_cb,
             const error_cb_t &ecb,
             const write_cb_t &wcb,
             uint8_t *failno);
    void run();
    void shutdown();
    void set_user_arg(const cio_conn_t &cc);
    void enable_read(const cio_conn_t &cc);
    void write(const cio_conn_t &cc, void *data, uint32_t len);
    void connect(const char *ip, uint16_t port, void *arg);
    void close(const cio_conn_t &cc);

private:
    void ign_sigpipe();
    void epoll_accept_cb(event_loop *loop, int fd, uint16_t event);
    uint16_t choose_loop();

    uint16_t thread_num_;
    std::vector<event_loop *> loops_;
    boost::thread_group threads_;
    int srvfd_;
    event_loop *main_loop_; //only use to handle listen,maybe timer
    boost::atomic<uint64_t> choosed_index_;
    accept_cb_t accept_cb_;
};

#endif


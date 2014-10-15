#include "io_tcp_impl.h"
#include "event_loop.h"
#include "socket_util.h"
#include "chef_assert.h"
#include "async_log.h"
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <boost/bind.hpp>

io_tcp_ptr io_tcp::create(const char *ip, int16_t port, uint16_t thread_num,
                          const accept_cb_t &acb, 
                          const connect_cb_t &connect_cb, 
                          const read_cb_t &rcb,
                          const close_cb_t &close_cb, 
                          const error_cb_t &ecb, 
                          const write_cb_t &wcb,
                          uint8_t *failno)
{
    io_tcp *obj = new io_tcp();
    int res = obj->impl_->init(ip, port, thread_num, acb, connect_cb, rcb, 
                close_cb, ecb, wcb, failno);
    if (res == -1) {
        delete obj;
        obj = nullptr;
    }
    return io_tcp_ptr(obj);
}

//void io_tcp::destroy(io_tcp *param)
//{
//    delete param; 
//}

io_tcp::io_tcp()
{
    impl_.reset(new io_tcp_impl());
}
io_tcp::~io_tcp()
{
}
void io_tcp::run()
{
    return impl_->run();
}
void io_tcp::shutdown()
{
    impl_->shutdown();
}
void io_tcp::set_user_arg(const cio_conn_t &cc)
{
    impl_->set_user_arg(cc);
}
void io_tcp::enable_read(const cio_conn_t &cc)
{
    impl_->enable_read(cc);
}
void io_tcp::write(const cio_conn_t &cc, void *data, uint32_t len)
{
    impl_->write(cc, data, len);
}
void io_tcp::connect(const char *ip, uint16_t port, void *arg)
{
    impl_->connect(ip, port, arg);
}
void io_tcp::close(const cio_conn_t &cc)
{
    impl_->close(cc);
}

io_tcp_impl::io_tcp_impl()
    : thread_num_(0)
    , srvfd_(-1)
    , main_loop_(nullptr)
    , choosed_index_(0)
{
}

io_tcp_impl::~io_tcp_impl()
{
    shutdown();
    threads_.join_all();
    for (const auto &loop : loops_) {
        delete loop;
    }
    if (srvfd_ != -1) {
        ::close(srvfd_);
        srvfd_ = -1;
    }
    if (main_loop_) {
        delete main_loop_;
        main_loop_ = nullptr;
    }
}

int io_tcp_impl::init(const char *ip, int16_t port, uint16_t thread_num,
                      const accept_cb_t &acb,
                      const connect_cb_t &connect_cb,
                      const read_cb_t &rcb,
                      const close_cb_t &close_cb,
                      const error_cb_t &ecb,
                      const write_cb_t &wcb,
                      uint8_t *failno)
{
    if (!ip || (port <= 0 && port != -1) || thread_num == 0) {
        if (failno) {
            *failno = 1;
        }
        return -1;
    }
    ign_sigpipe();
    if (port > 0) {
        srvfd_ = fetch_listen_socket(ip, port);
        if (srvfd_ == -1) {
            CHEF_TRACE_DEBUG("socket listen fail,ip=%s,port=%d.", ip, port);
            if (failno) {
                *failno = 2;
            }
            return -1;
        }
        make_socket_nonblock(srvfd_);
    }
    thread_num_ = thread_num;
    int i = 0;
    for (; i < thread_num; ++i) {
        loops_.push_back(new event_loop(i, acb, connect_cb, rcb, 
                    close_cb, ecb, wcb));
    }
    main_loop_ = new event_loop(i, acb, connect_cb, rcb, close_cb, ecb, wcb);
    main_loop_->init();
    if (port > 0) {
        main_loop_->add(srvfd_, boost::bind(&io_tcp_impl::epoll_accept_cb, this,
                    _1, _2, _3));
        main_loop_->modr(srvfd_, true);
    }

    if (failno) {
        *failno = 0;
    }
    return 0;
}

void io_tcp_impl::run()
{
    uint16_t i = 0;
    for (; i < thread_num_; ++i) {
        threads_.create_thread(boost::bind(&event_loop::thread_func, loops_[i]));
        loops_[i]->wait_inited();
        CHEF_TRACE_DEBUG("io loop %u start.", i);
    }
    CHEF_TRACE_DEBUG("main io loop start.");
    main_loop_->run();
    CHEF_TRACE_DEBUG("main io loop done stop.");
    threads_.join_all();
}

void io_tcp_impl::shutdown()
{
    if (main_loop_) {
        main_loop_->shutdown();
    }
    for (uint16_t i = 0; i < thread_num_; ++i) {
        loops_[i]->shutdown();
    }
}

void io_tcp_impl::ign_sigpipe()
{
    struct sigaction act;
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    CHEF_ASSERT(sigaction(SIGPIPE, &act, nullptr) == 0); 
}

void io_tcp_impl::epoll_accept_cb(event_loop *loop, int fd, uint16_t event)
{
    CHEF_ASSERT(loop == main_loop_ && fd == srvfd_);

    int sock = ::accept(fd, nullptr, nullptr);
    if (sock == -1) {
        return;
    }
    event_loop *choosed_loop = loops_[choose_loop()];
    choosed_loop->add_task(boost::bind(&event_loop::accept_in_loop, 
                choosed_loop, sock));
}

uint16_t io_tcp_impl::choose_loop()
{
    return ++choosed_index_ % thread_num_;
}

void io_tcp_impl::set_user_arg(const cio_conn_t &cc)
{
    CHEF_ASSERT(cc.thread_index_ < thread_num_);
    event_loop *loop = loops_[cc.thread_index_];
    if (loop->tid() == boost::this_thread::get_id()) {
        loop->set_user_arg_in_loop(cc);
    } else {
        loop->add_task(boost::bind(&event_loop::set_user_arg_in_loop,
                    loop, cc));
    }
}

void io_tcp_impl::enable_read(const cio_conn_t &cc)
{
    CHEF_ASSERT(cc.thread_index_ < thread_num_);
    event_loop *loop = loops_[cc.thread_index_];
    if (loop->tid() == boost::this_thread::get_id()) {
        loop->enable_read_in_loop(cc);
    } else {
        loop->add_task(boost::bind(&event_loop::enable_read_in_loop,
                    loop, cc));
    }
}

void io_tcp_impl::write(const cio_conn_t &cc, void *data, uint32_t len)
{
    CHEF_ASSERT(cc.thread_index_ < thread_num_);
    event_loop *loop = loops_[cc.thread_index_];
    if (loop->tid() == boost::this_thread::get_id()) {
        loop->write_in_loop(cc, data, len, false);
    } else {
        uint8_t *data_copy = new uint8_t[len];
        memcpy(data_copy, data, len);
        loop->add_task(boost::bind(&event_loop::write_in_loop,
                    loop, cc, data_copy, len, true));
    }
}

void io_tcp_impl::close(const cio_conn_t &cc)
{
    CHEF_ASSERT(cc.thread_index_ < thread_num_);
    event_loop *loop = loops_[cc.thread_index_];
    if (loop->tid() == boost::this_thread::get_id()) {
        loop->close_in_loop(cc);
    } else {
        loop->add_task(boost::bind(&event_loop::close_in_loop, loop, cc));
    }
}

void io_tcp_impl::connect(const char *ip, uint16_t port, void *arg)
{
    event_loop *choosed_loop = loops_[choose_loop()];
    if (choosed_loop->tid() == boost::this_thread::get_id()) {
        choosed_loop->connect_in_loop(std::string(ip), port, arg);
    } else {
        choosed_loop->add_task(boost::bind(&event_loop::connect_in_loop, 
                    choosed_loop, std::string(ip), port, arg));
    }
}


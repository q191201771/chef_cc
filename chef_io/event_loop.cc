#include "event_loop.h"
#include "socket_util.h"
#include "connection.h"
#include "chef_assert.h"
#include "chef_async_log.h"
#include <sys/prctl.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <boost/bind.hpp>
#include <boost/thread/locks.hpp>

static void default_accept_cb(cio_conn_t cc, const char *peer_ip, uint16_t peer_port)
{
}
static void default_connect_cb(cio_conn_t cc, connect_status status)
{
}
static void default_read_cb(cio_conn_t cc, void *buf, uint32_t len)
{
}
static void default_close_cb(cio_conn_t cc)
{
}
static void default_error_cb(cio_conn_t cc, uint8_t error_no)
{
}
static void default_write_cb(cio_conn_t cc, uint64_t succ_wrote, uint64_t pending_len)
{
}

event_loop::event_loop(uint16_t index, 
                       const accept_cb_t &acb,
                       const connect_cb_t &connect_cb,
                       const read_cb_t &rcb,
                       const close_cb_t &close_cb,
                       const error_cb_t &ecb,
                       const write_cb_t &wcb)
    : index_(index)
    , epfd_(-1)
    , epoll_args_(1024, nullptr)
    , conn_id_(0)
    , run_(false)
    , reacting_(false)
{
    accept_cb_ = acb ? acb : default_accept_cb;
    connect_cb_ = connect_cb ? connect_cb : default_connect_cb;
    read_cb_ = rcb ? rcb : default_read_cb;
    close_cb_ = close_cb ? close_cb : default_close_cb;
    error_cb_ = ecb ? ecb : default_error_cb;
    write_cb_ = wcb ? wcb : default_write_cb;
    wakefd_[0] = wakefd_[1] = -1;
}

event_loop::~event_loop()
{
    CHEF_ASSERT(id2conn_.size() == 0);
}

void event_loop::init()
{
    CHEF_ASSERT(epfd_ == -1);
    epfd_ = epoll_create1(EPOLL_CLOEXEC);
    CHEF_ASSERT(epfd_ != -1);
    CHEF_ASSERT(::pipe(wakefd_) != -1);
    add(wakefd_[0], boost::bind(&event_loop::wakeup_cb, this, _1, _2, _3));
    modr(wakefd_[0], true);
    tid_ = boost::this_thread::get_id();
    inited_.notify();
}

void event_loop::wait_inited()
{
    inited_.wait();
}

int event_loop::add(int fd, const epoll_cb_t &cb)
{
    int maxfd = epoll_args_.size() - 1;
    CHEF_ASSERT(fd >= 0);
    CHEF_ASSERT(epfd_ != -1);
    CHEF_ASSERT(fd > maxfd || (fd <= maxfd && !epoll_args_[fd]))

    CHEF_ASSERT(make_socket_nonblock(fd) == 0);
    make_socket_keepalive(fd);
    make_socket_nodelay(fd);
    
    epoll_arg *arg = epoll_arg_pool_.construct();
    arg->fd_ = fd;
    arg->event_ = epoll_event_none;
    arg->cb_ = cb;
    arg->is_del_ = false;

    if (fd > maxfd) {
        epoll_args_.resize(fd + 1);
        for (int i = 0; i < fd - maxfd; ++i) {
            epoll_args_[maxfd + 1 + i] = nullptr;
        }
    }
    epoll_args_[fd] = arg;
    struct epoll_event event = {0};
    event.data.ptr = (void *)arg;
    if (epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &event) == -1) {
        CHEF_ASSERT(0);
        epoll_arg_pool_.destroy(arg);
        epoll_args_[fd] = nullptr;
        return -1;
    }
    return 0;
}

void event_loop::del(int fd)
{
    CHEF_ASSERT(fd >= 0 && fd <= (int)epoll_args_.size() - 1);
    CHEF_ASSERT(epoll_args_[fd]);
    if (reacting_) {
        deferred_del_args_.push_back(epoll_args_[fd]);
        epoll_args_[fd]->is_del_ = true;
    } else {
        epoll_arg_pool_.destroy(epoll_args_[fd]);
    }
    CHEF_ASSERT(epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, nullptr) == 0);
    epoll_args_[fd] = nullptr;
}

void event_loop::thread_func()
{
    /// set thread name
    char thread_name[32] = {0};
    snprintf(thread_name, sizeof thread_name, "io_tcp%d", index_);
    ::prctl(PR_SET_NAME, thread_name);
    
    init();
    run();
}

void event_loop::run()
{
    CHEF_ASSERT(!run_);
    run_ = true;
    while (run_) {
        poll(100);
    }
    poll(0);
    cleanup();
}

void event_loop::shutdown()
{
    if (!run_) {
        return;
    }
    run_ = false;
}

void event_loop::cleanup()
{
    if (wakefd_[0] != -1) {
        ::close(wakefd_[0]);
        wakefd_[0] = -1;
    }
    if (wakefd_[1] != -1) {
        ::close(wakefd_[1]);
        wakefd_[1] = -1;
    }
    if (epfd_ != -1) {
        ::close(epfd_);
        epfd_ = -1;
    }
    for (const auto &val : epoll_args_) {
        if (val) {
            epoll_arg_pool_.destroy(val);
        }
    }
    epoll_args_.clear();

    for (const auto &val : deferred_del_args_) {
        if (val) {
            epoll_arg_pool_.destroy(val);
        }
    }
    deferred_del_args_.clear();

    for (const auto &val : deferred_del_conns_) {
        connection_pool_.destroy(val);
    }
    deferred_del_conns_.clear();
    
    {//lock
    boost::lock_guard<boost::mutex> guard(tasks_mutex_);
    tasks_.clear();
    }//unlock
    
    for (const auto &val : id2conn_) {
        connection_pool_.destroy(val.second);
    }
    id2conn_.clear();
}

void event_loop::mod(int fd)
{
    epoll_arg *arg = epoll_args_[fd];
    struct epoll_event event = {0};
    event.data.ptr = (void *)arg;
    event.events = ((arg->event_ & epoll_event_read) ? EPOLLIN : 0) |
                   ((arg->event_ & epoll_event_write) ? EPOLLOUT : 0);
    CHEF_ASSERT(epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, &event) != -1);
}

void event_loop::modr(int fd, bool flag)
{
    CHEF_ASSERT(fd <= (int)epoll_args_.size() - 1 && epoll_args_[fd]);
    if (flag) {
        epoll_args_[fd]->event_ |= epoll_event_read;
    } else {
        epoll_args_[fd]->event_ &= ~epoll_event_read;
    }
    mod(fd);
}

void event_loop::modw(int fd, bool flag)
{
    CHEF_ASSERT(fd <= (int)epoll_args_.size() - 1 && epoll_args_[fd]);
    if (flag) {
        epoll_args_[fd]->event_ |= epoll_event_write;
    } else {
        epoll_args_[fd]->event_ &= ~epoll_event_write;
    }
    mod(fd);
}

void event_loop::poll(int timeout_ms)
{
    CHEF_ASSERT(epfd_ != -1);
    reacting_ = false;
    run_task();
    
    struct epoll_event events[128];
    int numfd = epoll_wait(epfd_, events, 128, timeout_ms);
    if (numfd <= 0) {
        return;
    }

    reacting_ = true;
    for (int i = 0; i < numfd; ++i) {
        epoll_arg *arg = (epoll_arg *)events[i].data.ptr;
        if (arg->is_del_) {
            continue;
        }

        uint16_t event = epoll_event_none;
        if ((arg->event_ & epoll_event_read) && 
                (events[i].events & EPOLLIN)) {
            event |= epoll_event_read;
        }
        //can't else if
        if ((arg->event_ & epoll_event_write) && 
                (events[i].events & EPOLLOUT)) {
            event |= epoll_event_write;
        }
        if (events[i].events & (EPOLLERR | EPOLLHUP)) {
            event |= epoll_event_error;
        }
        arg->cb_(this, arg->fd_, event);
    }
    reacting_ = false; 
    for (const auto &val : deferred_del_args_) {
        epoll_arg_pool_.destroy(val);
    }
    deferred_del_args_.clear();
    
    for (const auto &val : deferred_del_conns_) {
        connection_pool_.destroy(val);
    }
    deferred_del_conns_.clear();
}

void event_loop::run_task()
{
    std::deque<task> tasks_copy;
    boost::unique_lock<boost::mutex> lock(tasks_mutex_);
    tasks_copy.swap(tasks_);
    lock.unlock();

    while(!tasks_copy.empty()) {
        task t = tasks_copy.front();
        tasks_copy.pop_front();
        t();
    }
}

void event_loop::add_task(const task &t)
{
    boost::unique_lock<boost::mutex> lock(tasks_mutex_);
    tasks_.push_back(t);
    lock.unlock();
    wakeup();
}

void event_loop::accept_in_loop(int fd)
{
    cio_conn_t cc;
    cc.thread_index_ = index_;
    cc.conn_id_ = ++conn_id_;
    cc.arg_ = nullptr;
    connection *conn = connection_pool_.construct(this, cc, fd);
    conn->set_link_status(status_linked);
    accept_cb_(conn->cio_conn(), conn->peer_ip(), conn->peer_port());
}

void event_loop::add(connection *conn)
{
    id2conn_.insert(std::pair<uint64_t, connection *>(conn_id_, conn));
}

void event_loop::del(connection *conn)
{
    id2conn_.erase(conn->cio_conn().conn_id_);
    if (reacting_) {
        deferred_del_conns_.push_back(conn);
    } else {
        connection_pool_.destroy(conn);
    } 
}

void event_loop::wakeup()
{
    while(wakefd_[1] != -1 && write(wakefd_[1], "", 1) == -1 && errno == EINTR);
}

void event_loop::wakeup_cb(event_loop *loop, int fd, uint16_t event)
{
    char buf[32];
    ssize_t len = read(wakefd_[0], buf, 32);	
    (void)len;
}

connection *event_loop::find_conn_by_id(uint64_t id)
{
    const auto &iter = id2conn_.find(id);
    return iter == id2conn_.end() ? nullptr : iter->second;
}

void event_loop::set_user_arg_in_loop(cio_conn_t cc)
{
    connection *conn = find_conn_by_id(cc.conn_id_);
    if (conn) {
        conn->set_cio_conn(cc);
    }
}

void event_loop::enable_read_in_loop(cio_conn_t cc)
{
    connection *conn = find_conn_by_id(cc.conn_id_);
    if (conn) {
        conn->enable_read(); 
    }
}

void event_loop::write_in_loop(cio_conn_t cc, 
                               void *data, 
                               uint32_t len, 
                               bool del_data)
{
    connection *conn = find_conn_by_id(cc.conn_id_);
    if (conn) {
        conn->write(data, len);
        if (del_data) {
            delete [](uint8_t *)data;
        }
    }
}

void event_loop::close_in_loop(cio_conn_t cc)
{
    connection *conn = find_conn_by_id(cc.conn_id_);
    if (conn) {
        CHEF_TRACE_DEBUG("close by self,conn=%p.", conn);
        conn->close_in_loop(); 
    }
}

void event_loop::connect_in_loop(std::string ip, uint16_t port, void *arg)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        CHEF_ASSERT(0);
        //maybe fire connect fail msg to user
        return;
    }
    CHEF_ASSERT(make_socket_nonblock(fd) == 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
    cio_conn_t cc;
    cc.thread_index_ = index_;
    cc.conn_id_ = ++conn_id_;
    cc.arg_ = arg;

    int ret = ::connect(fd, (sockaddr *)&addr, sizeof addr);
    if (ret == -1) {
        if (errno == EINPROGRESS || errno == EINTR) {
            connection *conn = connection_pool_.construct(this, cc, fd);
            conn->set_link_status(status_linking);
            conn->enable_write();
            connect_cb_(cc, connect_status::connecting);
        } else {
            ::close(fd);
            connect_cb_(cc, connect_status::fail);
        }
        return;
    }
    connection *conn = connection_pool_.construct(this, cc, fd);
    conn->set_link_status(status_linked);
    conn->enable_read();
    connect_cb_(cc, connect_status::connected);
}


#ifndef CHEF_CHEF_IO_EVENT_LOOP_H_
#define CHEF_CHEF_IO_EVENT_LOOP_H_

#include "io_tcp.h"
#include "wait_event.h"
#include <stdint.h>
#include <vector>
#include <deque>
#include <boost/unordered_map.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/pool/object_pool.hpp>

using namespace chef;

#define epoll_event_none  0x00
#define epoll_event_read  0x01
#define epoll_event_write 0x02
#define epoll_event_error 0x04

class event_loop;
class connection;

typedef boost::function<void()> task;
typedef boost::function<void(event_loop *, int, uint16_t)> epoll_cb_t;

class event_loop : public boost::noncopyable
{
public:
    event_loop(uint16_t index, 
               const accept_cb_t &acb,
               const connect_cb_t &connect_cb,
               const read_cb_t &rcb,
               const close_cb_t &close_cb,
               const error_cb_t &ecb,
               const write_cb_t &wcb);
    ~event_loop();

    void thread_func();//io thread
    void init();
    void run();
    void wait_inited();
    void shutdown();
    void poll(int timeout_ms);

    int add(int fd, const epoll_cb_t &cb);
    void del(int fd);
    void modr(int fd, bool flag);
    void modw(int fd, bool flag);

    void wakeup();
    void add_task(const task &t);
    void accept_in_loop(int fd);
    void set_user_arg_in_loop(cio_conn_t cc);
    void enable_read_in_loop(cio_conn_t cc);
    void write_in_loop(cio_conn_t cc, void *data, uint32_t len, bool del_data);
    void close_in_loop(cio_conn_t cc);
    void connect_in_loop(std::string ip, uint16_t port, void *arg);

    void add(connection *conn);
    void del(connection *conn);

    boost::thread::id tid() const {return tid_;}
    const connect_cb_t &connect_cb() const {return connect_cb_;}
    const read_cb_t &read_cb() const {return read_cb_;}
    const write_cb_t &write_cb() const {return write_cb_;}
    const error_cb_t &error_cb() const {return error_cb_;}
    const close_cb_t &close_cb() const {return close_cb_;}

private:
    void run_task();
    void wakeup_cb(event_loop *loop, int fd, uint16_t event);
    void mod(int fd);
    void cleanup();
    connection *find_conn_by_id(uint64_t id);

    struct epoll_arg
    {
        int fd_;
        uint16_t event_;
        epoll_cb_t cb_;
        bool is_del_;
    };   

    typedef std::vector<epoll_arg *> epoll_args;
    typedef std::vector<connection *> connections;
    typedef boost::unordered_map<uint64_t, connection *> id2conn;
    typedef boost::object_pool<connection> connection_pool;
    typedef boost::object_pool<epoll_arg> epoll_arg_pool;

    uint16_t index_;
    int wakefd_[2];
    int epfd_;
    wait_event inited_;
    epoll_args epoll_args_;
    epoll_args deferred_del_args_;
    connections deferred_del_conns_;
    std::deque<task> tasks_;
    boost::mutex tasks_mutex_;
    accept_cb_t accept_cb_;
    connect_cb_t connect_cb_;
    read_cb_t read_cb_;
    close_cb_t close_cb_;
    error_cb_t error_cb_;
    write_cb_t write_cb_;
    uint64_t conn_id_;
    id2conn id2conn_;
    bool run_;
    bool reacting_;
    boost::thread::id tid_;
    connection_pool connection_pool_;
    epoll_arg_pool epoll_arg_pool_;
};

#endif


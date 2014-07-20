#ifndef _CHEF_BASE_TASK_THREAD_H_
#define _CHEF_BASE_TASK_THREAD_H_

#include "_thread.h"
#include "wait_event.h"
#include <string>
#include <map>
#include <deque>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/noncopyable.hpp>

// *i want write an task_thread that not only can add task but also
//  can add some task deferred to run

//TODO
// *i use map instead heap to manager deferred task
//  because deferred task is few & we don't need that precise
// *except timeout, the inside epoll is only use for an pair of pipe which 
//  use to signal the epoll,it was not an common epoll work for net-io.KISS
// *task & deferred task can use 2 lock

namespace chef
{

class task_thread : public boost::noncopyable
{
public:
    typedef boost::function<void()> task;

    explicit task_thread(const std::string &name = std::string("task thread"));
    ~task_thread();

    void start();

    //0 means run ASAP
    //precise > 100ms
    void add(const task &t, uint32_t deferred_time_ms = 0);

private:
    void run_in_thread();
    void run_task();
    void run_deferred_task();

    int init_epoll();	
    int init_wakeup();
    void wakeup();
    int make_socket_nonblocking(int fd);
    int poll(int timeout);

private:
    std::string name_;
    bool run_;
    boost::scoped_ptr<thread> thread_;
    std::deque<task> tasks_;
    std::multimap<uint64_t, task> deferred_tasks_;
    boost::mutex lock_;

    int wakefd_[2];
    int epfd_;
    wait_event thread_run_up_;
};

} /// namespace chef
#endif


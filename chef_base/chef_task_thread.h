#ifndef _CHEF_CHEF_BASE_TASK_THREAD_H_
#define _CHEF_CHEF_BASE_TASK_THREAD_H_

#include "chef_wait_event.h"
#include <string>
#include <map>
#include <deque>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

namespace chef
{

class task_thread : public boost::noncopyable
{
public:
    typedef boost::function<void()> task;

    explicit task_thread(const std::string &name = std::string("task thread"));
    ~task_thread();

    /// non-block func
    void start();

    /**
     * @ param
     *  deferred_time_ms 0 means no deferred
     * @ brief
     *  deferred precise > 100ms
     */
    void add(const task &t, uint32_t deferred_time_ms = 0);

    uint32_t fetch_num_of_undone_task();

private:
    void run_in_thread(std::string name);
    //void run_deferred_task();
    void append_expired_task(std::deque<task> &tasks/*out*/);

private:
    std::string name_;
    bool run_;
    boost::scoped_ptr<boost::thread> thread_;
    std::deque<task> tasks_;
    std::multimap<uint64_t, task> deferred_tasks_;
    boost::mutex mutex_;
    boost::condition_variable cond_;
    wait_event thread_run_up_;
};

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_TASK_THREAD_H_


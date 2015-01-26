#ifndef _CHEF_CHEF_BASE_THREAD_POOL_H_
#define _CHEF_CHEF_BASE_THREAD_POOL_H_

#include "chef_wait_event.h"
#include <string>
#include <vector>
#include <deque>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>

namespace chef
{

class thread_pool : public boost::noncopyable
{
public:
    typedef boost::function<void()> task;

    explicit thread_pool(const std::string &name = std::string("thread poll"));
    ~thread_pool();

    /// non-block func
    void start(int thread_num);

    void add(const task &t);

private:
    void run_in_thread(uint16_t index);
    task take();

private:
    std::string name_;
    int thread_num_;
    std::vector<boost::shared_ptr<boost::thread> > threads_;
    std::vector<boost::shared_ptr<wait_event> > threads_run_up_;
    bool run_;
    std::deque<task> tasks_;
    boost::mutex mutex_;
    boost::condition_variable cond_;
};

} /// namespace chef
#endif /// _CHEF_CHEF_BASE_THREAD_POOL_H_


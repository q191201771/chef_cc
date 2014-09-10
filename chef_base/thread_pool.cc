#include "thread_pool.h"
#include "chef_assert.h"
#include <stdio.h>
#include <boost/thread/locks.hpp>
#include <boost/make_shared.hpp>

#ifdef __GNUC__
#include <sys/prctl.h>
#endif

namespace chef
{

thread_pool::thread_pool(const std::string &name) 
    : name_(name)
    , run_(false)
{
}

thread_pool::~thread_pool()
{
    /// FIXCHEF
    /// smome task lost..
    if (run_) {
        run_ = false;
        cond_.notify_all();
        for (int i = 0; i < thread_num_; ++i) {
            threads_[i]->join();
        }
    }
}

void thread_pool::start(int thread_num)
{
    CHEF_ASSERT(thread_num > 0);

    thread_num_ = thread_num;
    run_ = true;
    for (int i = 0; i < thread_num; ++i) {
        threads_run_up_.push_back(boost::make_shared<wait_event>());
        threads_.push_back(boost::make_shared<boost::thread>(
                boost::bind(&thread_pool::run_in_thread, this, i)));
        threads_run_up_[i]->wait();
    }
}

void thread_pool::add(const task &t)
{
    boost::unique_lock<boost::mutex> lock(mutex_);
    tasks_.push_back(t);
    lock.unlock();
    cond_.notify_one();
}

void thread_pool::run_in_thread(uint16_t index)
{
#ifdef __GNUC__
    char thread_name[32] = {0};
    snprintf(thread_name, 31, "%s%d", name_.c_str(), index + 1);
    ::prctl(PR_SET_NAME, thread_name);
#endif
    threads_run_up_[index]->notify();
    while(run_) {
        task t(take());
        if (t) {
            t();
        }
    }
}

thread_pool::task thread_pool::take()
{
    boost::unique_lock<boost::mutex> lock(mutex_);
    while(run_ && tasks_.empty()) {
        cond_.wait(lock);
    }

    task t;
    if (!tasks_.empty()) {
        t = tasks_.front();
        tasks_.pop_front();
    }

    return t;
}

} /// namespace chef


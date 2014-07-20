#include "thread_poll.h"
#include <stdio.h>
#include <assert.h>
#include <boost/thread/locks.hpp>
#include <boost/make_shared.hpp>

namespace chef
{

thread_poll::thread_poll(const std::string &name) : 
    name_(name),
    run_(true)
{

}

thread_poll::~thread_poll()
{
    //todo
    //join?
}

void thread_poll::start(int thread_num)
{
    assert(thread_num > 0);

    thread_num_ = thread_num;

    char thread_name[32] = {0};

    for (int i = 0; i < thread_num; ++i) {
        snprintf(thread_name, 31, "%s%d", name_.c_str(), i + 1);
        threads_.push_back(boost::make_shared<thread>(
                    boost::bind(&thread_poll::run_in_thread, this,i), thread_name));
        threads_run_up_.push_back(boost::make_shared<wait_event>());
        threads_[i]->start();
        threads_run_up_[i]->wait();
    }
}

void thread_poll::add(const task &t)
{
    boost::unique_lock<boost::mutex> lock(mutex_);
    tasks_.push_back(t);
    lock.unlock();
    cond_.notify_one();
}

void thread_poll::run_in_thread(uint16_t num)
{
    threads_run_up_[num]->notify();
    while(run_) {
        task t(take());
        if (t) {
            t();
        }
    }
}

thread_poll::task thread_poll::take()
{
    boost::unique_lock<boost::mutex> lock(mutex_);
    while(tasks_.empty()) {
        cond_.wait(lock);
    }

    task t;
    if (!tasks_.empty()) {
        t = tasks_.front();
    }
    tasks_.pop_front();

    return t;
}

} /// namespace chef


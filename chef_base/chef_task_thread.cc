#include "chef_task_thread.h"
#include <stdio.h>
#include <boost/chrono.hpp>

#ifdef __GNUC__
#include <sys/prctl.h>
#endif

namespace chef
{

task_thread::task_thread(const std::string &name)
    : name_(name)
    , run_(false)
    , thread_(NULL)
{
}

task_thread::~task_thread()
{
    //before dtor,some task have't done.
    //need?
    //do this for valgrind,but some deferred task may lost,though
    if (run_) {
        run_ = false;
        thread_->join();
    }
}

void task_thread::start()
{
    run_ = true;
    thread_.reset(new boost::thread(boost::bind(&task_thread::run_in_thread, this,
            name_)));
    thread_run_up_.wait();
}

void task_thread::add(const task &t, uint32_t deferred_time_ms)
{
    boost::lock_guard<boost::mutex> guard(mutex_); 
    if (deferred_time_ms == 0){
        tasks_.push_back(t);
    } else {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        uint64_t expire = ts.tv_sec * 1000 + ts.tv_nsec / 1000000 + deferred_time_ms;
        deferred_tasks_.insert(std::pair<uint64_t, task>(expire, t));
    }
    cond_.notify_one();
}

void task_thread::run_in_thread(std::string name)
{
#ifdef __GNUC__
    ::prctl(PR_SET_NAME, name.c_str());
#endif
    thread_run_up_.notify();
    std::deque<task> tasks_copy;

    while(run_) {
        { /// lock ctor
            boost::unique_lock<boost::mutex> lock(mutex_);
            cond_.wait_for(lock, boost::chrono::milliseconds(100));
            if (!tasks_.empty()) {
                tasks_copy.swap(tasks_);
            }
            //run_deferred_task();
            append_expired_task(tasks_copy);
        } /// lock dtor
        while (!tasks_copy.empty()) {
            task t = tasks_copy.front();
            tasks_copy.pop_front();
            t();
        }
    }
}

void task_thread::append_expired_task(std::deque<task> &tasks)
{
    /// most of time,deferred task is few
    if (deferred_tasks_.empty()) {
        return;
    }

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t now = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;

    auto iter = deferred_tasks_.begin();
    for (; iter != deferred_tasks_.end(); ++iter) {
        if (iter->first > now) {
            break;
        }

        tasks.push_back(iter->second);
    }
    deferred_tasks_.erase(deferred_tasks_.begin(), iter);

}

//void task_thread::run_deferred_task()
//{
//    /// most of time,deferred task is few
//    if (deferred_tasks_.empty()) {
//        return;
//    }
//
//    struct timespec ts;
//    clock_gettime(CLOCK_MONOTONIC, &ts);
//    uint64_t now = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
//
//    auto iter = deferred_tasks_.begin();
//    for (; iter != deferred_tasks_.end(); ++iter) {
//        if (iter->first > now) {
//            break;
//        }
//
//        (iter->second)();
//    }
//    deferred_tasks_.erase(deferred_tasks_.begin(), iter);
//}

uint32_t task_thread::fetch_num_of_undone_task()
{
    boost::lock_guard<boost::mutex> guard(mutex_);
    return tasks_.size() + deferred_tasks_.size();
}

} /// namespace chef

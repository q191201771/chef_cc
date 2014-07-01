#ifndef _CHEF_BASE_THREAD_POLL_H_
#define _CHEF_BASE_THREAD_POLL_H_

#include "_thread.h"
#include "wait_event.h"
#include <string>
#include <vector>
#include <deque>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/noncopyable.hpp>

//consider producer is fast than comsumer
//maybe we can write another produce scheme to block producer

class thread_poll : public boost::noncopyable
{
public:
    typedef boost::function<void()> task;

    explicit thread_poll(const std::string &name = std::string("thread poll"));
    ~thread_poll();

    void start(int thread_num);
    void add(const task &t);

private:
    void run_in_thread(uint16_t index);
    task take();

private:
    std::string name_;
    int thread_num_;
    std::vector<boost::shared_ptr<thread> > threads_;
    std::vector<boost::shared_ptr<wait_event> > threads_run_up_;
    bool run_;
    std::deque<task> tasks_;
    boost::mutex mutex_;
    boost::condition_variable cond_;
};

#endif


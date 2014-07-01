#ifndef _CHEF_BASE_WAIT_EVENT_H_
#define _CHEF_BASE_WAIT_EVENT_H_

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/condition_variable.hpp>

class wait_event : public boost::noncopyable
{
public:
    wait_event() :
        succ_(false)
    {}

    void notify()
    {
        boost::unique_lock<boost::mutex> lock(mutex_);
        succ_ = true;
        lock.unlock();
        cond_.notify_one();
    }

    void wait()
    {
        boost::unique_lock<boost::mutex> lock(mutex_);
        while (!succ_) {
            cond_.wait(lock);
        }
    }

private:
    boost::mutex mutex_;
    boost::condition_variable cond_;
    bool succ_;
};

#endif


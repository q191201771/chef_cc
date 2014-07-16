#ifndef _CHEF_BASE_MUTEX_H_
#define _CHEF_BASE_MUTEX_H_

#include "_noncopyable.h"
#include <assert.h>
#include <pthread.h>

/**
 * @switch to boost::mutex
 *            boost::lock_guard
 *            boost::unique_lock
 */

class mutex_lock : public noncopyable
{
public:
    mutex_lock()
    {
        pthread_mutex_init(&mutex_, NULL);
    }
    ~mutex_lock()
    {
        pthread_mutex_destroy(&mutex_);
    }

    void lock()
    {
        pthread_mutex_lock(&mutex_);	
    }

    void unlock()
    {
        pthread_mutex_unlock(&mutex_);
    }

    pthread_mutex_t &get_pthread_mutex_t() { return mutex_; }

private:
    pthread_mutex_t mutex_; 
};

class mutex_lock_guard : public noncopyable
{
public:
    explicit mutex_lock_guard(mutex_lock &ml) : 
        ml_(ml)
    {
        ml_.lock();
    }
    ~mutex_lock_guard()
    {
        ml_.unlock();
    }

private:
    mutex_lock &ml_;
};

#endif


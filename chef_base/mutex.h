#ifndef _CHEF_CHEF_BASE_MUTEX_H_
#define _CHEF_CHEF_BASE_MUTEX_H_

#include "noncopyable.h"
#include <assert.h>
#include <pthread.h>

/**
 * @switch to boost::mutex
 *            boost::lock_guard
 *            boost::unique_lock
 */

namespace chef
{

class mutex : public noncopyable
{
public:
    mutex() { pthread_mutex_init(&mutex_, NULL); }
    ~mutex() { pthread_mutex_destroy(&mutex_); }
    void lock() { pthread_mutex_lock(&mutex_); }
    bool try_lock() { return pthread_mutex_trylock(&mutex_) == 0; }
    void unlock() { pthread_mutex_unlock(&mutex_); }

    pthread_mutex_t &get_pthread_mutex_t() { return mutex_; }

private:
    pthread_mutex_t mutex_; 
};

class lock_guard : public noncopyable
{
public:
    explicit lock_guard(mutex &m) : m_(m) { m_.lock(); }
    ~lock_guard() { m_.unlock(); }

private:
    mutex &m_;
};

} /// namespace chef
#endif /// _CHEF_CHEF_BASE_MUTEX_H_


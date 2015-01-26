#ifndef _CHEF_CHEF_BASE_RWLOCK_H_
#define _CHEF_CHEF_BASE_RWLOCK_H_

#include <pthread.h>

/**
 * @switch to boost::share_mutex
 *            boost::share_lock
 */

namespace chef
{

class rwlock
{
public:
    rwlock() { pthread_rwlock_init(&core_, NULL); }
    ~rwlock() { pthread_rwlock_destroy(&core_); }
    void lockw() { pthread_rwlock_wrlock(&core_); }
    void lockr() { pthread_rwlock_rdlock(&core_); }
    void unlock() { pthread_rwlock_unlock(&core_); }
private:
    pthread_rwlock_t core_;
};

class read_locker
{
public:
    explicit read_locker(rwlock &lock) : lock_(lock) { lock_.lockr(); }
    ~read_locker() { lock_.unlock(); }
private:
    rwlock &lock_;
};

class write_locker
{
public:
    explicit write_locker(rwlock &lock) : lock_(lock) { lock_.lockw(); }
    ~write_locker() { lock_.unlock(); }
private:
    rwlock &lock_;
};

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_RWLOCK_H_


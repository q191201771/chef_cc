#ifndef _CHEF_CHEF_BASE_SPIN_LOCK_H_
#define _CHEF_CHEF_BASE_SPIN_LOCK_H_

#include <pthread.h>
#include <boost/noncopyable.hpp>

namespace chef
{

class spin_lock
{
public:
    spin_lock() { pthread_spin_init(&core_, 0); }
    ~spin_lock() { pthread_spin_destroy(&core_); }
    void lock() { pthread_spin_lock(&core_); }
    bool try_lock() { return pthread_spin_trylock(&core_) == 0; }
    void unlock() { pthread_spin_unlock(&core_); }

    /// pthread_spin_lock_t &get_mutable_core() { return core_; }
private:
    pthread_spinlock_t core_;
};

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_SPIN_LOCK_H_


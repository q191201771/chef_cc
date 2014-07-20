#ifndef CHEF_BASE_ATOMIC_H_
#define CHEF_BASE_ATOMIC_H_

#include "_noncopyable.h"
#include <stdint.h>

/**
 * @switch to boost::atomic
 */

namespace chef
{

template <typename T>
class atomic : public noncopyable
{
public:
    atomic() : value_(0) {}

    T get()
    {
        return __sync_val_compare_and_swap(&value_, 0, 0);	
    }

    void set(T v)
    {
        __sync_lock_test_and_set(&value_, v);
    }

    //add an nagative num means subtraction
    T add_and_get(T v)
    {
        return get_and_add(v) + v;
    }

    T increment()
    {
        return add_and_get(1);
    }

    T decrement()
    {
        return add_and_get(-1);
    }

private:	

    T get_and_add(T v)
    {
        return __sync_fetch_and_add(&value_, v);
    }

private:
    volatile T value_;
};

typedef atomic<int32_t> atomic_int32_t;
typedef atomic<int64_t> atomic_int64_t;
typedef atomic<uint64_t> atomic_uint64_t;
typedef atomic<uint16_t> atomic_uint16_t;

} /// namespace chef
#endif


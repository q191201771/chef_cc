#include "_atomic.h" 
#include "assert_.h"
#define CHEF_ASSERT_LEVEL 1
#include <boost/thread.hpp>

const int thread_num =10;

atomic_int32_t val;

/// 0 1 2 3 4 5  6  7  8  9
/// 1 2 3 6 7 12 13 20 21 30
void fun(int index)
{
    if (index % 2) {
        val.add_and_get(index);
    } else {
        val.increment();
    }
}

int main()
{
    printf(">atomic_test.\n");
    CHEF_ASSERT(val.get() == 0);
    val.set(0);
    CHEF_ASSERT(val.get() == 0);
    val.set(10);
    CHEF_ASSERT(val.get() == 10);
    CHEF_ASSERT(val.add_and_get(20) == 30);
    CHEF_ASSERT(val.increment() == 31);
    CHEF_ASSERT(val.decrement() == 30);
    CHEF_ASSERT(val.add_and_get(-30) == 0);

    boost::thread *ts[thread_num];
    int i = 0;
    for (; i < thread_num; ++i) {
        ts[i] = new boost::thread(boost::bind(fun, i));
    }
    i = 0;
    for (; i < thread_num; ++i) {
        ts[i]->join();
        delete ts[i];
    }

    CHEF_ASSERT(val.get() == 30);
    printf("<atomic_test.\n");

    return 0;
}


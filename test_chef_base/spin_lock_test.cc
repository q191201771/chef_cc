#include "spin_lock.h"
#include "_mutex.h"
#include "async_log.h"
#include <boost/thread.hpp>

chef::mutex g_mutex;
chef::spin_lock g_spin;
int64_t g_num = 0;

const int LOOP_TIMES = 10000000;

void mutex_test()
{
    for (int i = 0; i < LOOP_TIMES; ++i) {
        chef::lock_guard guard(g_mutex);
        ++g_num;
    }
}

void spin_test()
{
    for (int i = 0; i < LOOP_TIMES; ++i) {
        g_spin.lock();
        --g_num;
        g_spin.unlock();
    }
}

int main()
{   
    printf(">spin_lock_test.\n");
    const int THREAD_NUM = 2;

    chef::async_log::get_mutable_instance().init(chef::async_log::debug, false);
    boost::thread *threads[THREAD_NUM];
    CHEF_TRACE_DEBUG(">mutex.");
    for (int i = 0; i < THREAD_NUM; ++i) {
        threads[i] = new boost::thread(boost::bind(&mutex_test));
    }
    for (int i = 0; i < THREAD_NUM; ++i) {
        threads[i]->join();
        delete threads[i];
        threads[i] = NULL;
    }
    CHEF_TRACE_DEBUG("<mutex.");

    CHEF_TRACE_DEBUG(">spin.");
    for (int i = 0; i < THREAD_NUM; ++i) {
        threads[i] = new boost::thread(boost::bind(&spin_test));
    }
    for (int i = 0; i < THREAD_NUM; ++i) {
        threads[i]->join();
        delete threads[i];
    }
    CHEF_TRACE_DEBUG("<spin.");
    assert(g_num == 0);
    printf("<spin_lock_test.\n");

    return 0;
}


#include "_rwlock.h"
#include "_thread.h"
#include "async_log.h"

rwlock g_lock;
uint64_t g_count = 0;

void increment()
{
    for (; ; ) {
        usleep(1);
        write_locker wl(&g_lock);
        CHEF_TRACE_DEBUG("entered write lock.");
        ++g_count;
        CHEF_TRACE_DEBUG("leaving write lock.");
    }
}

void print()
{
    for (; ; ) {
        usleep(1);
        read_locker rl(&g_lock);
        CHEF_TRACE_DEBUG("entered read lock.");
        CHEF_TRACE_DEBUG("%lu", g_count);
        CHEF_TRACE_DEBUG("leaving read lock.");
    }
}

int main()
{
    chef::async_log::get_mutable_instance().init();

    thread *write_thds[16];
    for (int i = 0; i < 2; ++i) {
        write_thds[i] = new thread(boost::bind(&increment));
        write_thds[i]->start();
    }

    thread *read_thds[16];
    for (int i = 0; i < 4; ++i) {
        read_thds[i] = new thread(boost::bind(&print));
        read_thds[i]->start();
    }
    getchar();
    //deleteeeee

    return 0;   
}


#include "thread_pool.h"
#include "async_log.h"

void fun(int i)
{
    CHEF_TRACE_DEBUG("%d", i);
}

int main()
{
    printf(">thread_pool_test.\n");
    chef::async_log::get_mutable_instance().init(chef::async_log::debug, false);
    chef::thread_pool tp;
    for (int i = 0; i < 128; ++i) {
        tp.add(boost::bind(&fun, i));
    }
    tp.start(4);
    for (int i = 128; i < 256; ++i) {
        tp.add(boost::bind(&fun, i));
    }
    sleep(1);
    printf("<thread_pool_test.\n");

    return 0;
}


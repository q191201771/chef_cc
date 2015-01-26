#include "chef_thread_pool.h"
#include "chef_async_log.h"
#include "chef_current_thd.h"
#include <assert.h>

void fun(int i)
{
    CHEF_TRACE_DEBUG("    %d", i);
}

int main()
{
    printf(">thread_pool_test.\n");
    int ret = chef::async_log::get_mutable_instance().init(chef::async_log::debug, true);
    assert(ret == 0);
    chef::thread_pool tp;
    for (int i = 0; i < 128; ++i) {
        tp.add(boost::bind(&fun, i));
    }
    tp.start(4);
    for (int i = 128; i < 256; ++i) {
        tp.add(boost::bind(&fun, i));
    }
    chef::current_thd::sleep_ms(1000);
    printf("<thread_pool_test.\n");

    return 0;
}


#include "chef_async_log.h"
#include "chef_assert.h"
#include "chef_current_thd.h"
#include <stdint.h>
#include <assert.h>
#include <vector>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

typedef boost::shared_ptr<boost::thread> thread_ptr;
typedef std::vector<thread_ptr > thread_vec;

void fun(int i)
{
    chef::async_log::get_mutable_instance().trace(chef::async_log::fatal, __FILE__,
            __LINE__, __func__, "%d", i);
    CHEF_TRACE_ERROR("%d", i);
    CHEF_TRACE_WARN("%d", i);
    CHEF_TRACE_INFO("%d", i);
    CHEF_TRACE_DEBUG("%d", i);
}

int main()
{
    int ret = 0;
    const int THREAD_NUM = 32;

    printf(">async_log_test.\n");
    CHEF_TRACE_DEBUG("u can't see me in log.");
    ret = chef::async_log::get_mutable_instance().trace(chef::async_log::debug, __FILE__,
            __LINE__, __func__, "u can't see me in log.");
    assert(ret == -1);
    /// if async_log mode true, some log may not flush to file in this unit test
    ret = chef::async_log::get_mutable_instance().init(chef::async_log::info, false,
            "../log/"/*, "tmp.log.chef"*/);
    assert(ret == 0);
    ret = chef::async_log::get_mutable_instance().init(chef::async_log::info, true,
            "../log/"/*, "tmp.log.chef"*/);
    assert(ret == -1);

    thread_vec tv;
    for (int i = 0; i < THREAD_NUM; ++i) {
        tv.push_back(thread_ptr(new boost::thread(boost::bind(fun, i))));
    }

    ret = chef::async_log::get_mutable_instance().trace(chef::async_log::fatal, __FILE__,
            __LINE__, __func__, "1");
    assert(ret == 0);
    CHEF_TRACE_ERROR("2");
    CHEF_TRACE_WARN("3");
    CHEF_TRACE_INFO("4");
    CHEF_TRACE_DEBUG("5");
    CHEF_TRACE_DEBUG("u can't see me in log.");
    ret = chef::async_log::get_mutable_instance().trace(chef::async_log::debug, __FILE__,
            __LINE__, __func__, "u can't see me in log.");
    assert(ret == 0);
    CHEF_ASSERT(0);
    for (int i = 0; i < THREAD_NUM; ++i) {
        tv[i]->join();
    }
    //chef::current_thd::sleep_ms(1500);
    printf("<async_log_test.\n");

    return 0;   
}


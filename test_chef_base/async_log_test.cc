#include "async_log.h"
#include "assert_.h"
#include <stdint.h>
#include <vector>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

typedef boost::shared_ptr<boost::thread> thread_ptr;
typedef std::vector<thread_ptr > thread_vec;

void fun(int i)
{
    CHEF_TRACE_FATAL("%d", i);
    CHEF_TRACE_ERROR("%d", i);
    CHEF_TRACE_WARN("%d", i);
    CHEF_TRACE_INFO("%d", i);
    CHEF_TRACE_DEBUG("%d", i);
}

int main()
{
    printf(">async_log_test.\n");
    CHEF_TRACE_DEBUG("u can't see me in log.");
    /// if async_log mode true, some log may not flush to file in this test
    chef::async_log::get_mutable_instance().init(chef::async_log::debug, true);

    thread_vec tv;
    for (int i = 0; i < 16; ++i) {
        tv.push_back(thread_ptr(new boost::thread(boost::bind(fun, i))));
    }

    CHEF_TRACE_FATAL("1");
    CHEF_TRACE_ERROR("2");
    CHEF_TRACE_WARN("3");
    CHEF_TRACE_INFO("4");
    CHEF_TRACE_DEBUG("5");
    CHEF_ASSERT(0);
    for (int i = 0; i < 16; ++i) {
        tv[i]->join();
    }
    printf("<async_log_test.\n");

    return 0;   
}


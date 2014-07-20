#include "async_log.h"
#include "assert_.h"
#include <inttypes.h>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/pool.hpp>

class A
{
public:
    A(uint64_t val)
    {
    }
    ~A()
    {   
        printf("~A().\n");
    }
    void fun()
    {
    }
};

int main()
{
    chef::async_log::get_mutable_instance().init(chef::async_log::debug, false);
    CHEF_TRACE_DEBUG("hello");
    CHEF_ASSERT(0);

    boost::object_pool<A> pl;
//    pl.construct(100);
//    return 0;

    CHEF_TRACE_DEBUG("round 1.");
    for (int i = 0; i < 1 * 50; ++i) {
        for (int j = 0; j < 10000 * 10000; ++j) {
            A *p2 = new A(i);
            delete p2;
        }
    }
    CHEF_TRACE_DEBUG("round 1 done.");
   
    CHEF_TRACE_DEBUG("round 2.");
    for (int i = 0; i < 1 * 50; ++i) {
        for (int j = 0; j < 10000 * 10000; ++j) {
            A *p = pl.construct(i);
            pl.destroy(p);
        }
    }
    CHEF_TRACE_DEBUG("round 2 done.");
    printf("done.\n");
    return 0;   
}


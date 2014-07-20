#include "_condition.h"
#include <boost/thread.hpp>
using chef::mutex;
using chef::condition;

mutex m2;
condition  c2(m2);

void fun()
{
    sleep(1);
    c2.notify();
}

int main()
{
    printf(">condition_test.\n");
    /// won't wake up
//    mutex m1;
//    condition c1(m1);
//    c1.notify();
//    c1.wait();
    
    boost::thread t(fun);
    c2.wait();

    printf("<condition_test.\n");
    return 0;
}


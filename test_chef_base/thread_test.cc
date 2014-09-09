#include "thread.h"
#include "current_thd.h"
#include <assert.h>
using chef::thread;

int tid = 0;

int add(int a, int b)
{
    //printf("add().\n");
    tid = chef::current_thd::gettid();
    return a + b;
}

int main()
{
    printf(">thread_test.\n");
    thread thd1(boost::bind(&add, 1, 2));
    assert((int)thd1.gettid() == 0);
    assert(thd1.try_join() == -1);
    /// will assert inside
    //thd1.join();

    thd1.start();
//    printf("~.\n");
//    chef::current_thd::sleep_ms(3000); /// let add() execute over
//    printf("!.\n");
    thd1.join();
//    printf("@.\n");
    assert(thd1.gettid() == tid); 
    printf("<thread_test.\n");

    return 0;
}


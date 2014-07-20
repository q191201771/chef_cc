#include "_mutex.h"
#include <stdio.h>
using chef::mutex;
using chef::lock_guard;

int main()
{
    printf(">mutex_test.\n");
    mutex m;
    m.lock();
    m.unlock();
    {
    lock_guard lg(m);
    }

    /// not recursive,will block
    //m.lock();
    //m.lock();

//    m.unlock();
//    m.unlock();
//    m.unlock();
//    m.lock();
//    m.lock();
//    m.unlock();
    printf("<mutex_test.\n");

    return 0;
}


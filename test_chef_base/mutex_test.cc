#include "chef_mutex.h"
#include <stdio.h>
using chef::mutex;
using chef::lock_guard;

int main()
{
    printf(">mutex_test.\n");
    mutex m;
    assert(m.try_lock() == true);
    //m.lock(); /// not recursive,will block
    m.unlock();
    m.lock();
    assert(m.try_lock() == false);
    m.unlock();
    {
    lock_guard lg(m);
    }
    printf("<mutex_test.\n");

    return 0;
}


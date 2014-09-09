#include "rwlock.h"
#include <stdio.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
using chef::rwlock;
using chef::read_locker;
using chef::write_locker;

chef::rwlock lock;
bool flag = false;

void read()
{
    read_locker rl(lock);
    assert(!flag);
}
void write()
{
    write_locker wl(lock);
    flag = true;
    flag = false;
}

int main()
{
    printf(">rwlock.\n");
    /// figure out read-lock recursive,write-lock not
//    lock.lockw();
//    printf("#.\n");
//    lock.lockr();
//    printf("~.\n");
//    lock.lockr();
//    printf("!.\n");
//    lock.lockw();
//    printf("@.\n");

    boost::thread *arr[1024];
    int i = 0;
    for (; i < 1024; ++i) {
        if (i % 2) {
            arr[i] = new boost::thread(boost::bind(read));
        } else {
            arr[i] = new boost::thread(boost::bind(write));
        }
    }
    for (i = 0; i < 1024; ++i) {
        arr[i]->join();
        delete arr[i];
    }
    printf("<rwlock.\n");
    return 0;
}


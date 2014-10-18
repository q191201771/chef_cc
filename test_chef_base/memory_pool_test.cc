#include "memory_pool.h"
#include <stdio.h>

static int count = 0;

class A
{
public:
    A() 
    { 
//        printf("A(),%d.\n", ++count); 
        p_ = new char[1024];
        memset(p_, 'x', 1024);
    }
    ~A() 
    { 
//        printf("~A(), %d.\n", --count); 
        delete []p_;
    }
private:
    static int count_;
    char *p_;
};

int main()
{
    (void)count;
    printf(">memory_pool_test.\n");
    chef::memory_pool<A> *pool = chef::memory_pool<A>::create(8);
    if (!pool) {
        printf("memory_pool::create fail.\n");
        return 0;
    }
//    printf("after create 8.\n");
    A *a[17] = {0};
    for (int i = 0; i < 17; ++i) {
        a[i] = pool->pop();
        if (!a[i]) {
            printf("memory_pool::pop fail.\n");
            return 0;
        }
    }
//    printf("after pop 17.\n");
    pool->push(a[0]);
//    printf("after push.\n");
    chef::memory_pool<A>::destory(pool);
//    printf("after destory.\n");
    for (int i = 1; i < 17; ++i) {
        delete a[i];
    }
    printf("<memory_pool_test.\n");
    return 0;
}

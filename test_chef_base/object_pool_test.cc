#define CHEF_UNIT_TEST
#include "object_pool.h"
#include <stdio.h>
#include <assert.h>

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
    printf(">object_pool_test.\n");
    chef::object_pool<A> *pool = chef::object_pool<A>::create(8);
    if (!pool) {
        printf("object_pool::create fail.\n");
        return 0;
    }
    assert(pool->get_outstanding() == 0);
//    printf("after create 8.\n");
    A *a[17] = {0};
    for (int i = 0; i < 17; ++i) {
        a[i] = pool->pop();
        if (!a[i]) {
            printf("object_pool::pop fail.\n");
            return 0;
        }
    }
    assert(pool->get_outstanding() == 17);
//    printf("after pop 17.\n");
    pool->push(a[0]);
    assert(pool->get_outstanding() == 16);
//    printf("after push.\n");
    chef::object_pool<A>::destory(pool);
//    printf("after destory.\n");
    for (int i = 1; i < 17; ++i) {
        delete a[i];
    }
    printf("<object_pool_test.\n");
    return 0;
}

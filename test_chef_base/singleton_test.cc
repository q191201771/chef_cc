#include "chef_singleton.h"
#include "chef_thread.h"
#include <assert.h>

bool flag = true;

class A {
    public:
        A() {
            assert(flag);
            flag = false;
        }
        ~A() {
        }
        void fun() {
            assert(!flag);
        }
};

void fun() {
    chef::singleton<A>::instance().fun();
}

int main()
{
    printf(">singleton_test.\n");
    chef::singleton<A>::instance().fun();
    for (int i = 0; i < 128; ++i) {
        chef::thread t(fun);
        t.start();
    }
    chef::singleton<A>::instance().fun();
    printf("<singleton_test.\n");
    return 0;
}

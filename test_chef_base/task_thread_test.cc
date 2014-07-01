#include "task_thread.h"
#include "async_log.h"

void fun1()
{
    CHEF_TRACE_DEBUG("fun1().");
}

void fun2(char *buf)
{
    CHEF_TRACE_DEBUG("fun2(),%s.", buf);
    delete []buf;
}

class A
{
public:
    A()
    {
        buf_ = new char[4096];
    }
    ~A()
    {
        CHEF_TRACE_DEBUG("~A().");
        delete []buf_;
    }
    void fun3()
    {
        CHEF_TRACE_DEBUG("fun3().");
        delete this;
    }
    void fun4(char *buf)
    {
        CHEF_TRACE_DEBUG("fun4(),%s.", buf);
        delete []buf;
        delete this;
    }

private:
    char *buf_;
};

task_thread *tt = NULL;

void thread_fun()
{
    CHEF_TRACE_DEBUG("thread_fun().");
    for (int i = 0; i < 10000; ++i) {
        tt->add(fun1, i);
        char *buf = new char[1024];
        memset(buf, 'a', 1024);
        buf[1023] = '\0';
        tt->add(boost::bind(fun2, buf));
        A *a1 = new A();
        tt->add(boost::bind(&A::fun3, a1));
        A *a2 = new A();
        char *buf2 = new char[512];
        memset(buf2, 'b', 512);
        buf2[511] = '\0';
        tt->add(boost::bind(&A::fun4, a2, buf2), 10000 - i);
    }
}

int main()
{
    chef::async_log::get_mutable_instance().init(chef::async_log::debug, false, false);
    CHEF_TRACE_DEBUG("hello world.");

    tt = new task_thread("tt");
    tt->start();
    thread *ts[16];
    for (int i = 0; i < 16; ++i) {
        ts[i] = new thread(thread_fun);
        ts[i]->start();
    }
    
    CHEF_TRACE_DEBUG("waiting.");
    for (int i = 0; i < 16; ++i) {
        ts[i]->join();
        delete ts[i];
    }
    CHEF_TRACE_DEBUG("before tt dtor.");
    delete tt;
    CHEF_TRACE_DEBUG("after tt dtor.");

    return 0;
}

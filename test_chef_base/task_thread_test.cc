#include "task_thread.h"
#include "current_thd.h"

void fun(int var)
{
    printf("    %d.\n", var);
}

int main()
{
    printf(">task_thread_test.\n");
    chef::task_thread *tt = new chef::task_thread("tt");
    tt->start();
    tt->add(boost::bind(&fun, 3), 200);
    tt->add(boost::bind(&fun, 4), 300);
    tt->add(boost::bind(&fun, 1));
    tt->add(boost::bind(&fun, 2));
    chef::current_thd::sleep_ms(500);
    delete tt;
    printf("<task_thread_test.\n");
    return 0;
}

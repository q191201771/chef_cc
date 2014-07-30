#include "task_thread.h"

void fun(int var)
{
    printf("%d.\n", var);
}

int main()
{
    chef::task_thread *tt = new chef::task_thread("tt");
    tt->start();

    tt->add(boost::bind(&fun, 0), 1000);
    tt->add(boost::bind(&fun, 1));
    tt->add(boost::bind(&fun, 2));
    tt->add(boost::bind(&fun, 3), 5000);

    getchar();
    delete tt;

    return 0;
}

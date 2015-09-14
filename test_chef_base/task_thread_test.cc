#include "chef_task_thread.h"
#include "chef_current_thd.h"

chef::task_thread tt("tt");

void fun(int var)
{
    printf("    %d.\n", var);
}

int g_tick = 0;
void timer()
{
    printf("    timer:%d.\n", g_tick++);
    if (g_tick < 5) {
        tt.add(boost::bind(&timer), 100);
    }
}

int main()
{
    printf(">task_thread_test.\n");
    tt.start();
    tt.add(boost::bind(&fun, 3), 200);
    tt.add(boost::bind(&fun, 4), 300);
    tt.add(boost::bind(&fun, 1));
    tt.add(boost::bind(&fun, 2));
    chef::current_thd::sleep_ms(500);
    tt.add(boost::bind(&timer), 100);
    chef::current_thd::sleep_ms(1000);
    printf("<task_thread_test.\n");
    return 0;
}

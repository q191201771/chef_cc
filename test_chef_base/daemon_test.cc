#include "async_log.h"
#include "daemon.h"
#include "current_thd.h"
#include "current_proc.h"

int main()
{
    int ppid = chef::current_proc::getpid();

    if (chef::daemon_init("pid.daemon_test") == -1) {
        /// stdout redirect to /dev/null,more info man 3 daemon
        //printf("chef::daemon_init()==-1");
        return 0;
    }
    chef::async_log::get_mutable_instance().init();
    for (int i = 0; i != 60; ++i) {
        CHEF_TRACE_DEBUG("%d %d %d", ppid, chef::current_proc::getpid(), i);
        chef::current_thd::sleep_ms(1000);
    }
    chef::daemon_exit("pid.daemon_test");
    CHEF_TRACE_DEBUG("<main.");
    return 0;
}


#include "async_log.h"
#include "daemon.h"
#include "current_thd.h"

int main()
{
    if (chef::daemon_init("pid.daemon_test") == -1) {
        /// stdout redirect to /dev/null,more info man 3 daemon
        //printf("chef::daemon_init()==-1");
        return 0;
    }
    chef::async_log::get_mutable_instance().init();
    for (int i = 0; ; ) {
        CHEF_TRACE_DEBUG("%d", ++i);
        chef::current_thd::sleep_ms(1000);
    }
    chef::daemon_exit("pid.daemon_test");

    return 0;
}


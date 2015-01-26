#include "chef_daemon.h"
#include "chef_current_proc.h"

int main()
{
    std::string dir = chef::current_proc::obtain_bin_dir();
    dir += "pid.daemon_test";
    chef::daemon_init(dir.c_str());
    printf("u can't see me.\n");
    chef::daemon_exit(dir.c_str());
    return 0;
}


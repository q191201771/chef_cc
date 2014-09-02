#include "current_proc.h"

int main()
{
    printf(">current_proc_test.\n");
    printf("%s\n", chef::current_proc::obtain_bin_path().c_str());
    printf("%s\n", chef::current_proc::obtain_bin_name().c_str());
    printf("%s\n", chef::current_proc::obtain_bin_dir().c_str());
    printf("<current_proc_test.\n");
    return 0;
}


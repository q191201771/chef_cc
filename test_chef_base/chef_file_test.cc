#include "chef_file.h"
#include <assert.h>
#include <stdio.h>

int main()
{
    printf(">chef_file_test.\n");
    assert(chef::file_or_dir_exist("/usr") == 0);
    assert(chef::is_file("/usr") == -1);
    assert(chef::is_dir("/usr/") == 0);
    assert(chef::file_or_dir_exist("./chef_file_test") == 0);
    assert(chef::is_file("./chef_file_test") == 0);
    assert(chef::is_dir("chef_file_test") == -1);
    printf("<chef_file_test.\n");
    return 0;
}

#include "chef_file.h"
#include "uuid.h"
#include "current_proc.h"
#include <assert.h>
#include <stdio.h>

int main()
{
    printf(">chef_file_test.\n");
    assert(chef::mkdir_recursive("/tmp") == 0);
    /// authority for write.
    //assert(chef::mkdir_recursive("/bin/tmp.chef") == -1);
    std::string dir_name = "/tmp/";
    dir_name += chef::uuid::create();
    assert(chef::mkdir_recursive(dir_name.c_str()) == 0);
    printf("    mkdir %s succ.\n", dir_name.c_str());
    dir_name = std::string("/tmp/") + chef::uuid::create() + "/tmp1/";
    assert(chef::mkdir_recursive(dir_name.c_str()) == 0);
    printf("    mkdir %s succ.\n", dir_name.c_str());
    assert(chef::file_or_dir_exist(dir_name.c_str()) == 0);
    assert(chef::delete_folder(NULL) == -1);
    assert(chef::delete_folder(dir_name.c_str()) == 0);
    printf("    delete_folder %s succ.\n", dir_name.c_str());
    assert(chef::is_file("/usr") == -1);
    assert(chef::is_dir("/usr/") == 0);
    dir_name = chef::uuid::create();
    assert(chef::mkdir_recursive(dir_name.c_str()) == 0);
    printf("    mkdir %s succ.\n", dir_name.c_str());
    assert(chef::is_dir(dir_name.c_str()) == 0);
    printf("    is_dir %s succ.\n", dir_name.c_str());
    assert(chef::delete_folder(dir_name.c_str()) == 0);
    printf("    delete_folder %s succ.\n", dir_name.c_str());
    printf("<chef_file_test.\n");
    return 0;
}

#ifndef _CHEF_CHEF_BASE_CHEF_FILE_H_
#define _CHEF_CHEF_BASE_CHEF_FILE_H_

/// @ brief
///  @ without spefic brief, return 0 succ, -1 fail
///  @ abs dir and relative dir are both works.
///  @ more info see test_chef_base/chef_file_test.cc

namespace chef
{
    /// @ function : mkdir_recursive
    /// @ notice: if [dir] already exist before mkdir_recursive,return 0.
    int mkdir_recursive(const char *dir);
    int file_or_dir_exist(const char *name);
    int is_dir(const char *name);
    int is_file(const char *name);
    int delete_file(const char *name);
    int delete_folder(const char *name);

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_CHEF_FILE_H_

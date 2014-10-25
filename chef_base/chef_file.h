#ifndef _CHEF_CHEF_BASE_CHEF_FILE_H_
#define _CHEF_CHEF_BASE_CHEF_FILE_H_

/// @ brief
///  with no spefic brief, return 0 succ, -1 fail

namespace chef
{
    int file_or_dir_exist(const char *name);
    int is_dir(const char *name);
    int is_file(const char *name);

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_CHEF_FILE_H_

#include "chef_file.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace chef
{

int file_or_dir_exist(const char *name)
{
    struct stat st;
    return stat(name, &st);
}

int is_dir(const char *name)
{
    struct stat st;
    if (stat(name, &st) == -1) {
        return -1;
    }
    return S_ISDIR(st.st_mode) ? 0 : -1;
}

int is_file(const char *name)
{
    struct stat st;
    if (stat(name, &st) == -1) {
        return -1;
    }
    return S_ISREG(st.st_mode) ? 0 : -1;
}

} /// namespace chef


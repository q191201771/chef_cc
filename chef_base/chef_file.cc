#include "chef_file.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

namespace chef
{

int mkdir_recursive(const char *dir)
{
    if (!dir) {
        return -1;
    }
    char *dir_dup = strdup(dir);
    int len = strlen(dir_dup);
    if (len == 0) {
        return -1;
    }
    int i = dir_dup[0] == '/' ? 1 : 0;
    for (; i <= len; ++i) {
        if (dir_dup[i] == '/' || dir_dup[i] == '\0') {
            char ch = dir_dup[i];
            dir_dup[i] = '\0';
            if (mkdir(dir_dup, 0755) == -1 && errno != EEXIST) {
                free(dir_dup);
                return -1;
            }
            dir_dup[i] = ch;
        }
    }
    free(dir_dup);
    return 0;
}

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


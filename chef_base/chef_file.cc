#include "chef_file.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define IF_NULL_RETURN_FAIL(x) \
    { \
    if (!(x)) { \
        fprintf(stderr, "%s:%d\n", __func__, __LINE__); \
        return -1; \
    } \
    }

namespace chef
{

int mkdir_recursive(const char *dir)
{
    IF_NULL_RETURN_FAIL(dir);
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
    IF_NULL_RETURN_FAIL(name);
    struct stat st;
    return stat(name, &st);
}

int is_dir(const char *name)
{
    IF_NULL_RETURN_FAIL(name);
    struct stat st;
    if (stat(name, &st) == -1) {
        return -1;
    }
    return S_ISDIR(st.st_mode) ? 0 : -1;
}

int is_file(const char *name)
{
    IF_NULL_RETURN_FAIL(name);
    struct stat st;
    if (stat(name, &st) == -1) {
        return -1;
    }
    return S_ISREG(st.st_mode) ? 0 : -1;
}

int delete_file(const char *name)
{
    IF_NULL_RETURN_FAIL(name);
    if (remove(name) != 0) {
        fprintf(stderr, "remove(%s) fail,reason:%s.", name, strerror(errno));
        return -1;
    }
    return 0;
}

int delete_folder(const char *name)
{
    IF_NULL_RETURN_FAIL(name);
    char cmd[128] = {0};
    snprintf(cmd, 128, "rm -rf %s", name);
    if (system(cmd) == -1) {
        fprintf(stderr, "system(%s) fail.", cmd);
        return -1;
    }

    return 0;
}

} /// namespace chef


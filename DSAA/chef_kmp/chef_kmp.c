#include "chef_kmp.h"
#include <stdlib.h>

static
int chef_strlen(const char *data)
{
    int i = 0;
    for (; *(data + i) != '\0'; ++i);
    return i;
}

static
int chef_strncmp(const char *a, const char *b, int n)
{
    int i = 0;
    for (; i < n; ++i) {
        if (a[i] < b[i]) {
            return -1;
        } else if (a[i] > b[i]) {
            return 1;
        }
    }
    return 0;
}

int chef_kmp(const char *target, const char *pattern) 
{
    int target_len, pattern_len, i, j, k, max;
    int *next = NULL;
    target_len = pattern_len = i = j = k = max = 0;

    target_len = chef_strlen(target);
    pattern_len = chef_strlen(pattern);
    if (target_len < pattern_len) {
        return -1;
    }

    /// * compute next
    next = (int *)malloc(pattern_len * sizeof(int));
    i = 0;
    for (; i < pattern_len; ++i) {
        if (i == 0 || i == 1) {
            next[i] = 0;
            continue;
        }
        max = j = 0;
        for (; j < i - 1; ++j) {
            if (chef_strncmp(pattern, pattern + i - j - 1, j + 1) == 0) {
                if (j + 1 > max) {
                    max = j + 1;
                }
            }
        }
        next[i] = max;
    }
    /// * compute next end.

    i = j = 0;
    for (; i < target_len;) {
        if (target[i] == pattern[j]) {
            ++i;
            ++j;
            if (j == pattern_len) {
                free(next);
                return i - pattern_len;
            }
        } else {
            if (j == 0) {
                ++i;
            }
            j = next[j];
        }
    }

    free(next);
    return -1;
}

int chef_bf(const char *target, const char *pattern) 
{
    int target_len, pattern_len, i, j, k, max;
    target_len = pattern_len = i = j = k = max = 0;

    target_len = chef_strlen(target);
    pattern_len = chef_strlen(pattern);
    if (target_len < pattern_len) {
        return -1;
    }
    
    i = 0;
    for (; i < target_len - pattern_len + 1;++i) {
        if (chef_strncmp(target + i, pattern, pattern_len) == 0) {
            return i;
        }
    }

    return -1;
}


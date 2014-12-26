#include "chef_kmp.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/// used strlen & strncmp

int chef_kmp(const char *target, const char *pattern) 
{
    int target_len, pattern_len, i, j, k, max;
    int *next = NULL;
    target_len = pattern_len = i = j = k = max = 0;

    if (target == NULL || pattern == NULL) {
        return -1;
    }
    target_len = strlen(target);
    pattern_len = strlen(pattern);
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
            if (strncmp(pattern, pattern + i - j - 1, j + 1) == 0) {
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


#include "chef_kmp.h"
#include <string.h>
#include <stdlib.h>

/// used strlen & strncmp

int kmp(const char *target, const char *pattern) 
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
            next[i] = 1;
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
        next[i] = i - max;
    }
    /// * compute next end.

    i = j = 0;
    for (; i < target_len - pattern_len + 1;) {
        if (target[i + j] == pattern[j]) {
            if (++j == pattern_len) {
                free(next);
                return i;
            }
        } else {
            /// NOTICE
            /// if mod i+= next[j]; to ++i;
            /// that will be BF(Brute-Force)
            i += next[j];
            j = 0;
        }
    }

    free(next);
    return -1;
}


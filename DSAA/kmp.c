#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//strlen
//strncmp

/**
 * @function: kmp
 * @return: -1 not matched,otherwise the position of "target" that matched
 *          "pattern".
 */
static int 
kmp(const char *target, const char *pattern) {
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
            i += next[j];
            j = 0;
        }
    }

    free(next);
    return -1;
}

static int 
TEST_KMP(const char *target, const char *pattern)
{
    int i = 0;
    printf("<<<<<<<<<<<<<<<<<<<<\n");
    printf(" target: %s\npattern: %s\n", target, pattern);
    int ret = kmp(target, pattern);
    if (ret == -1) {
        printf(" result: not match.\n");
    } else {
        printf(" result: %s\n", target);
        for (; i < ret; ++i) {
            printf(" ");
        }
        printf("         %s\n", pattern);
    }
    printf(">>>>>>>>>>>>>>>>>>>>\n");
    return ret;
}

int main(int argc, char **argv)
{
    assert(TEST_KMP("a", "b") == -1);
    assert(TEST_KMP("a", "a") == 0);
    assert(TEST_KMP("a", "ab") == -1);
    assert(TEST_KMP("ab", "a") == 0);
    assert(TEST_KMP("ab", "b") == 1);
    assert(TEST_KMP("ababcababa", "ababa") == 5);
    assert(TEST_KMP("abacaabacabacabaabb", "abacab") == 5);
    assert(TEST_KMP("BBC ABCDAB ABCDABCDABDE", "ABCDABD") == 15);
    assert(TEST_KMP("a b c d e a b c d e a b c d f", "c d f") == 24);
    return 0;
}


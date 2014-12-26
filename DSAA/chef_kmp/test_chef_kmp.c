#include "chef_kmp.h"
#include <stdio.h>
#include <assert.h>

int TEST_KMP(const char *target, const char *pattern)
{
    int i = 0;
    printf("<<<<<<<<<<<<<<<<<<<<\n");
    printf(" target: %s\npattern: %s\n", target, pattern);
    int ret = chef_kmp(target, pattern);
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

int TEST_BF(const char *target, const char *pattern)
{
    int i = 0;
    printf("<<<<<<<<<<<<<<<<<<<<\n");
    printf(" target: %s\npattern: %s\n", target, pattern);
    int ret = chef_kmp(target, pattern);
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
    printf(">test_chef_kmp.\n-----kmp-----\n");
    assert(TEST_KMP("a", "b") == -1);
    assert(TEST_KMP("a", "a") == 0);
    assert(TEST_KMP("a", "ab") == -1);
    assert(TEST_KMP("ab", "a") == 0);
    assert(TEST_KMP("ab", "b") == 1);
    assert(TEST_KMP("ababcababa", "ababa") == 5);
    assert(TEST_KMP("abacaabacabacabaabb", "abacab") == 5);
    assert(TEST_KMP("BBC ABCDAB ABCDABCDABDE", "ABCDABD") == 15);
    assert(TEST_KMP("a b c d e a b c d e a b c d f", "c d f") == 24);
    
    printf("-----bf-----\n");
    assert(TEST_BF("a", "b") == -1);
    assert(TEST_BF("a", "a") == 0);
    assert(TEST_BF("a", "ab") == -1);
    assert(TEST_BF("ab", "a") == 0);
    assert(TEST_BF("ab", "b") == 1);
    assert(TEST_BF("ababcababa", "ababa") == 5);
    assert(TEST_BF("abacaabacabacabaabb", "abacab") == 5);
    assert(TEST_BF("BBC ABCDAB ABCDABCDABDE", "ABCDABD") == 15);
    assert(TEST_BF("a b c d e a b c d e a b c d f", "c d f") == 24);
    printf("<test_chef_kmp.\n");

    return 0;
}


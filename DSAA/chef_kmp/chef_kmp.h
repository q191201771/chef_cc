#ifndef _CHEF_CHEF_KMP_H_
#define _CHEF_CHEF_KMP_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * KMP O(m+n)
 * BF  O(mn)
 */

/**
 * @function: chef_kmp
 * @return: -1 not matched,otherwise the position of "target" that matched "pattern".
 */
int chef_kmp(const char *target, const char *pattern);

/**
 * @brief: use Brute Force
 */
int chef_bf(const char *target, const char *pattern);

//int chef_strlen(const char *data);
//int chef_strncmp(const char *a, const char *b, int n);

#ifdef __cplusplus
}
#endif

#endif /// _CHEF_CHEF_KMP_H_


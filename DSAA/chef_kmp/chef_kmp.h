#ifndef _CHEF_CHEF_KMP_H_
#define _CHEF_CHEF_KMP_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @function: chef_kmp
 * @return: -1 not matched,otherwise the position of "target" that matched "pattern".
 */
int chef_kmp(const char *target, const char *pattern);

#ifdef __cplusplus
}
#endif

#endif /// _CHEF_CHEF_KMP_H_


/**
 * Reverse digits of an integer.
 *
 * Example1: x = 123, return 321
 * Example2: x = -123, return -321
 *
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Solution {
    public:
        int reverse(int x) {
            int ret;
            bool positive;
            if (x >= 0) {
                positive = true;
            } else {
                positive = false;
                x = -x;
            }
            char buf[32] = {0};
            snprintf(buf, 32, "%d", x);
            int i = 0;
            int j = strlen(buf) - 1;
            while(i < j) {
                char tmp = buf[i];
                buf[i] = buf[j];
                buf[j] = tmp;
                ++i;
                --j;
            }
            ret = atoi(buf);
            if (ret == 0x7FFFFFFF) {
                return 0;
            } 
            return positive ? ret : -ret;
        }
};

int main()
{
    Solution s;
    assert(s.reverse(123) == 321);
    assert(s.reverse(-123) == -321);

    return 0;
}


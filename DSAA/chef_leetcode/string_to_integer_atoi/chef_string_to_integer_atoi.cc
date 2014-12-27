/**
 * Implement atoi to convert a string to an integer.
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

class Solution {
    public:
        int atoi(const char *str) {
            int ret = 0;
            bool positive = true;
            int len = strlen(str);
            int index = 0;
            char *trimed_str = (char *)malloc(len);
            memset(trimed_str, 0, len);

            /// *1. trim front ' '
            for (; index < len; ++index) {
                if (str[index] != ' ') {
                    break;
                }
            }

            /// *2. check positive symbol
            if (str[index] == '-') {
                positive = false;
                ++index;
            } else if (str[index] == '+') {
                positive = true;
                ++index;
            }
            
            /// *3. trim front '0'
            for (; index < len; ++index) {
                if (str[index] != '0') {
                    break;
                }
            }
            
            /// *4. trim back
            int i = len - 1;
            int first = -1;
            for (; i > index; --i) {
                if (ctoi_(str[i]) == -1) {
                    first = i;
                }
            }
            if (first != -1) {
                len = first;
            }
            
            /// *5. oh yeah
            for (; index < len; ++index) {
                int now = ctoi_(str[index]);
                if (now == -1) {
                    return 0;
                }
                if (positive && ret > (MAX_INT - now) / 10) {
                    return MAX_INT;
                }
                if (!positive && -ret < (MIN_INT + now) / 10) {
                    return MIN_INT;
                }
                ret = ret * 10 + now;
            }

            return positive ? ret : -ret;
        }
    private:
        int ctoi_(char ch) {
            if (ch >= '0' && ch <= '9') {
                return ch - '0';
            }
            return -1;
        }

    private:
        static const int MAX_INT = 2147483647;
        static const int MIN_INT = -MAX_INT - 1;
};

int main()
{
    Solution s;
    assert(s.atoi("     +004500") == 4500);
    assert(s.atoi("  -0012a42") == -12);
    assert(s.atoi("2147483648") == 2147483647);
    assert(s.atoi("-2147483649") == -2147483648);
    assert(s.atoi("23a8f") == 23);
    assert(s.atoi("   - 321") == 0);

    return 0;
}


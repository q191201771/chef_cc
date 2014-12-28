/**
 * Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.
 *
 * If the last word does not exist, return 0.
 *
 * Note: A word is defined as a character sequence consists of non-space characters only.
 *
 * For example, 
 * Given s = "Hello World",
 * return 5.
 */

#include <assert.h>
#include <stdio.h>

class Solution {
    public:
        int lengthOfLastWord(const char *s) {
            if (!s) {
                return 0;
            }
            int len = 0;
            for (; s[len] != '\0'; ++len);

            for (int i = len - 1; i >=0; --i) {
                if (s[i] == ' ') {
                    --len;
                } else {
                    break;
                }
            }

            for (int i = len - 1; i >= 0; --i) {
                if (s[i] == ' ') {
                    return len - i - 1;
                }
            }
            return len;
        }
};

int main()
{
    Solution s;

    char str1[] = "a";
    char str2[] = "a ";
    assert(s.lengthOfLastWord(str1) == 1);
    assert(s.lengthOfLastWord(str2) == 1);

    return 0;
}


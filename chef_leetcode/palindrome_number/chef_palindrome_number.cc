/**
 * Determine whether an integer is a palindrome. Do this without extra space.
 */

#include <assert.h>
#include <stdio.h>

class Solution {
    public:
        bool isPalindrome(int x) {
            if (x < 0) {
                return false;
            }
            int y = 0;
            int bak = x;
            for (int i = 1; ; i *= 10) {
                y *= 10;
                y += x % 10;
                if ((x /= 10) == 0) {
                    break;
                }
            }
            return bak == y;
        }
};

int main()
{
    Solution s;
    assert(s.isPalindrome(-2147483648) == false);
    assert(s.isPalindrome(1000021) == false);
    assert(s.isPalindrome(121) == true);
    assert(s.isPalindrome(1001) == true);
    assert(s.isPalindrome(10) == false);

    return 0;
}


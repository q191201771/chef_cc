/**
 * Given a string S, find the longest palindromic substring in S. You may assume
 * that the maximum length of S is 1000, and there exists one unique longest
 * palindromic substring.
 */

#include <stdio.h>
#include <string>
using namespace std;

class Solution {
    public:
        /// time out
//        bool check(const string &s, int left, int len) {
//            for (int right = left + len - 1; left <= right; ++left, --right) {
//                if (s[left] != s[right]) {
//                    return false;
//                }
//            }
//            return true;
//        }
//
//        string longestPalindrome(string s) {
//            if (s.length() <= 1) {
//                return s;
//            }
//            int left = 0;
//            int len = s.length();
//            for (; len > 0; --len) {
//                for (int left = 0; left < s.length() - len; ++left) {
//                    if (check(s, left, len)) {
//                        return s.substr(left, len);
//                    }
//                }
//            }
//            return string();
//        }

        string find(const string &s, int left, int right) {
            for (; left >= 0 && right < s.length() && s[left] == s[right]; --left, ++right);
            return s.substr(left + 1, right - left - 1);
        }

        string longestPalindrome(string s) {
            if (s.length() <= 1) {
                return s;
            }
            int len = s.length();
            string str, ret;
            for (int i = 0; i < len - 1; ++i) {
                str = find(s, i, i);
                if (str.length() > ret.length()) {
                    ret = str;
                }
                str = find(s, i , i + 1);
                if (str.length() > ret.length()) {
                    ret = str;
                }
            }
            return ret;
        }

};

int main()
{
    Solution s;
    string ret = s.longestPalindrome("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    printf("%s\n", ret.c_str());

    return 0;
}


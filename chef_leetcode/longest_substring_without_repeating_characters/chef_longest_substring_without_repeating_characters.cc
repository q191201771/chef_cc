/*
 * Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
 */

// "wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco"
// 12

#include <stdio.h>
#include <assert.h>
#include <string>
#include <map>
using namespace std;

class Solution {
    public:
        int lengthOfLongestSubstring(string s) {
            map<char, int> sub;
            int ret = 0;
            int start = 0;
            for (int i = 0; i < s.length(); ++i) {
                if (sub.find(s[i]) != sub.end() && sub[s[i]] >= start) {
                    int len = i - start;
                    if (len > ret) {
                        ret = len;
                    }
                    start = sub[s[i]] + 1;
                }
                sub[s[i]] = i;
            }
            if (s.length() - start > ret) {
                ret = s.length() - start;
            }
            return ret;
        }
};

int main()
{
    Solution s;
    assert(s.lengthOfLongestSubstring("qopubjguxhxdipfzwswybgfylqvjzhar") == 12);
    assert(s.lengthOfLongestSubstring("wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco") == 12);

    return 0;
}


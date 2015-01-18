/*
 * Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
 * 
 * For "(()", the longest valid parentheses substring is "()", which has length = 2.
 * 
 * Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
 * 
 */

/// "()(()"
/// "(()(((()"
/// "()()"
/// "(()"
class Solution {
    public:
        int longestValidParentheses(string s) {
            stack<int> lefts;
            int ret = 0;
            int pos = -1;

            for (int i = 0; i < s.length(); ++i) {
                if (s[i] == '(') {
                    lefts.push(i);
                } else {
                    if (lefts.size() > 0) {
                        lefts.pop();
                        int len;
                        if (lefts.empty()) {
                            len = i - pos;
                        } else {
                            len = i - lefts.top();
                        }
                        if (len > ret) {
                            ret = len;
                        }

                    } else {
                        pos = i;
                    }
                }
            }
            return ret;
        }
};

/**
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 * 
 * The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
 */

#include <stdio.h>
#include <string>
using namespace std;

class Solution {
    public:
        bool isValid(string s) {
            int len = s.length();
            if (len <= 0) {
                return false;
            }
            string stack;
            for (int i = 0; i < len; ++i) {
                if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
                    stack += s[i];
                } else if (s[i] == ')') {
                    if (stack.rbegin() != stack.rend() && *(stack.rbegin()) == '(') {
                        stack.erase(stack.end() - 1);
                    } else {
                        return false;
                    }
                } else if (s[i] == '}') {
                    if (stack.rbegin() != stack.rend() && *(stack.rbegin()) == '{') {
                        stack.erase(stack.end() - 1);
                    } else {
                        return false;
                    }
                } else if (s[i] == ']') {
                    if (stack.rbegin() != stack.rend() && *(stack.rbegin()) == '[') {
                        stack.erase(stack.end() - 1);
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
            
            return stack.length() == 0;
        }
};

int main()
{
    Solution s;
    bool ret = s.isValid(string("()[]{}"));
    printf("ret=%s\n", ret ? "true" : "false");

    return 0;
}

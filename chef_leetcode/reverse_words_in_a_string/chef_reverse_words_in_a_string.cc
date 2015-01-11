/**
 * Given an input string, reverse the string word by word.
 * 
 * For example,
 *     Given s = "the sky is blue",
 *     return "blue is sky the".
 * 
 *     click to show clarification.
 * 
 *     Clarification:
 *     What constitutes a word?
 *     A sequence of non-space characters constitutes a word.
 *     Could the input string contain leading or trailing spaces?
 *     Yes. However, your reversed string should not contain leading or trailing spaces.
 *     How about multiple spaces between two words?
 *     Reduce them to a single space in the reversed string.
 */

/// input: ""
/// input: " " output: ""
/// input: "a" output: "a"
class Solution {
    public:
        void reverseWords(string &s) {
            if (s == string()) {
                return;
            }
            stack<string> words;
            int l = -1;
            for (int i = 0; i < s.size(); ++i) {
                if (s[i] == ' ') {
                    if (l == -1) {
                        continue;
                    } else {
                        words.push(string(s, l, i - l));
                        l = -1;
                    }
                } else {
                    if (l == -1) {
                        l = i;
                    }
                }
            }
            if (l != -1) {
                words.push(string(s, l));
            }
            s.clear();
            while(!words.empty()) {
                s += words.top();
                words.pop();
                if (!words.empty()) {
                    s += " ";
                }
            }
        }
};

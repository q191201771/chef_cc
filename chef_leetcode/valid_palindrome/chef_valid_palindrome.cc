/**
 * Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
 * 
 * For example,
 *     "A man, a plan, a canal: Panama" is a palindrome.
 *     "race a car" is not a palindrome.
 * 
 *     Note:
 *     Have you consider that the string might be empty? This is a good question to ask during an interview.
 * 
 *     For the purpose of this problem, we define empty string as valid palindrome.
 */

class Solution {
    public:
        bool isPalindrome(string s) {
            int pos = 0;
            for (int i = 0; i < s.length(); ++i) {
                if (s[i] >= 'A' && s[i] <= 'Z') {
                    s[pos++] = s[i] - 'A' + 'a';
                } else if ((s[i] >= 'a' && s[i] <= 'z')
                        || (s[i] >= '0' && s[i] <= '9')) {
                    s[pos++] = s[i];
                }
            }
            s.resize(pos);
            for (int j = 0; j < s.length() / 2; ++j) {
                if (s[j] != s[s.length() - 1 - j]) {
                    return false;
                }
            }
            return true;
        }
};


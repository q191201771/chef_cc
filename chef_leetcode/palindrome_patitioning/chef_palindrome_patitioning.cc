/**
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * 
 * Return all possible palindrome partitioning of s.
 * 
 * For example, given s = "aab",
 *     Return
 * 
 *       [
 *           ["aa","b"],
 *           ["a","a","b"]
 *       ]
 */

class Solution {
    public:
        bool is_palindrome(string str) {
            for (int i = 0; i < str.length() / 2; ++i) {
                if (str[i] != str[str.length() - i - 1]) {
                    return false;
                }
            }
            return true;
        }

        void compute(int index) {
            if (index == s_.size()) {
                result_.push_back(vec_);
                return;
            }
            std::string str;
            for (int i = index; i < s_.size(); ++i) {
                str = s_.substr(index, i - index + 1);
                if (is_palindrome(str)) {
                    vec_.push_back(str);
                    compute(i + 1);
                    vec_.pop_back();
                }
            }
        }

        vector<vector<string> > partition(string s) {
            s_ = s;
            compute(0);
            return result_;
        }
    private:
        string s_;
        vector<string> vec_;
        vector<vector<string> > result_;
};


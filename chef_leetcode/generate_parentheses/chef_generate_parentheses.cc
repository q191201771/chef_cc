/**
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
 * 
 * For example, given n = 3, a solution set is:
 * 
 * "((()))", "(()())", "(())()", "()(())", "()()()"
 */

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

class Solution {
    public:
        int left_valid(int index) {
            int count = 0;
            for (int i = 0; i < index; ++i) {
                if (str_[i] == '(') {
                    if (++count == n_) {
                        return 0;
                    }
                }
            }
            return 1;
        }

        int right_valid(int index) {
            int left_count = 0;
            int right_count = 0;
            for (int i = 0; i < index; ++i) {
                if (str_[i] == '(') {
                    ++left_count;
                } else {
                    ++right_count;
                }
            }
            if (right_count == n_ || left_count == right_count) {
                return 0;
            }
            return 1;
        }

        void compute(int index) {
            if (index == n_ * 2) {
                result_.push_back(string(str_.c_str()));
                return;
            }
            if (left_valid(index) == 1) {
                str_[index] = '(';
                compute(index + 1);
            }
            if (right_valid(index) == 1) {
                str_[index] = ')';
                compute(index + 1);
            }
        }

        vector<string> generateParenthesis(int n) {
            n_ = n;
            compute(0);
            return result_;
        }
    private:
        int n_;
        string str_;
        vector<string> result_;
};

int main(int argc, char **argv)
{
    int n = 3;
    if (argc == 2) {
        n = atoi(argv[1]);
    }
    Solution s;
    vector<string> ret = s.generateParenthesis(n);
    printf("size=%d.\n", ret.size());
    for (int i = 0; i < ret.size(); ++i) {
        printf("%s\n", ret[i].c_str());
    }
    return 0;
}


/**
 * Given a collection of integers that might contain duplicates, S, return all possible subsets.
 *
 * Note:
 * Elements in a subset must be in non-descending order.
 * The solution set must not contain duplicate subsets.
 * For example,
 * If S = [1,2,2], a solution is:
 * 
 * [
 *   [2],
 *   [1],
 *   [1,2,2],
 *   [2,2],
 *   [1,2],
 *   []
 * ]
 */

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    public:
        void compute(int index) {
            if (index == vec_.size()) {
                return;
            }

            for (int i = index; i < vec_.size();) {
                int j = i + 1;
                for (; j < vec_.size(); ++j) {
                    if (vec_[i] != vec_[j]) {
                        break;
                    }
                }
                for (int k = 1; k < j - i + 1; ++k) {
                    for (int m = 0; m < k; ++m) {
                        sub_.push_back(vec_[i + m]);
                    }
                    ret_.push_back(sub_);
                    compute(j);
                    for (int m = 0; m < k; ++m) {
                        sub_.pop_back();
                    }
                }
                i += j - i;
            }
        }

        vector<vector<int> > subsetsWithDup(vector<int> &S) {
            vec_ = S;
            std::sort(vec_.begin(), vec_.end());
            ret_.push_back(sub_);
            compute(0);
            return ret_;
        }

    private:
        vector<int> vec_;
        vector<int> sub_;
        vector<vector<int> > ret_;
};

int main()
{
    Solution s;
    vector<int> S;
    S.push_back(1);
    S.push_back(1);
    s.subsetsWithDup(S);

    return 0;
}


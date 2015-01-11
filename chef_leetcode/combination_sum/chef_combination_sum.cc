/**
 * Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
 * 
 * The same repeated number may be chosen from C unlimited number of times.
 * 
 * Note:
 * All numbers (including target) will be positive integers.
 * Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
 * The solution set must not contain duplicate combinations.
 * For example, given candidate set 2,3,6,7 and target 7, 
 *     A solution set is: 
 *     [7] 
 *     [2, 2, 3]
 */

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    public:
        bool match() {
        }

        void compute(int begin) {
            for (int i = begin; i < cadidates_.size(); ++i) {
                array_.push_back(cadidates_[i]);
                sum_ += cadidates_[i];
                if (sum_ < target_) {
                    compute(i);
                } else if (sum_ == target_) {
                    result_.push_back(array_);
                    array_.pop_back();
                    sum_ -= cadidates_[i];
                    return;
                } else { }
                array_.pop_back();
                sum_ -= cadidates_[i];
            }
        }

        vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
            cadidates_ = candidates;
            sort(cadidates_.begin(), cadidates_.end());
            target_ = target;
            sum_ = 0;
            compute(0);
            return result_;
        }
    private:
        vector<int> cadidates_;
        int target_;
        vector<int> array_;
        int sum_;
        vector<vector<int> > result_;
};

/// input: [2] 1
/// input: [1,2] 3 output: [1,1,1] [1,2]
/// input: [1,2] 4 output: [[1111],[1,1,2],[2,2]]

int main()
{
    Solution s;
    vector<int> c;
    c.push_back(8);
    c.push_back(7);
    c.push_back(4);
    c.push_back(3);
    vector<vector<int> > ret = s.combinationSum(c, 11);
    for (int i = 0; i < ret.size(); ++i) {
        for (int j = 0; j < ret[i].size(); ++j) {
            printf("%d ", ret[i][j]);
        }
        printf("\n");
    }

    return 0;
}

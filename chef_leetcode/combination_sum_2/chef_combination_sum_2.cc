/**
 * Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
 * 
 * Each number in C may only be used once in the combination.
 * 
 * Note:
 * All numbers (including target) will be positive integers.
 * Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
 * The solution set must not contain duplicate combinations.
 * For example, given candidate set 10,1,2,7,6,1,5 and target 8, 
 *     A solution set is: 
 *     [1, 7] 
 *     [1, 2, 5] 
 *     [2, 6] 
 *     [1, 1, 6]
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
                if (i > begin && cadidates_[i] == cadidates_[i - 1]) {
                    continue;
                }
                array_.push_back(cadidates_[i]);
                sum_ += cadidates_[i];
                if (sum_ < target_) {
                    compute(i + 1);
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

        vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
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

int main()
{
    Solution s;
    vector<int> c;
    c.push_back(10);
    c.push_back(1);
    c.push_back(2);
    c.push_back(7);
    c.push_back(6);
    c.push_back(1);
    c.push_back(5);
    vector<vector<int> > ret = s.combinationSum2(c, 8);
    for (int i = 0; i < ret.size(); ++i) {
        for (int j = 0; j < ret[i].size(); ++j) {
            printf("%d ", ret[i][j]);
        }
        printf("\n");
    }

    return 0;
}

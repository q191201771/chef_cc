/**
 * Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
 * 
 * For example,
 *     If n = 4 and k = 2, a solution is:
 * 
 *     [
 *       [2,4],
 *       [3,4],
 *       [2,3],
 *       [1,2],
 *       [1,3],
 *       [1,4],
 *     ]
 */

#include <stdio.h>
#include <vector>
using namespace std;

class Solution {
    public:
        int valid(int index) {
            if (index == 0) {
                return 1;
            }
            return array_[index] > array_[index - 1];
        }

        void compute(int index) {
            if (index == k_) {
                result_.push_back(array_);
                return;
            }

            for (int i = 1; i <= n_; ++i) {
                array_[index] = i;
                if (valid(index) == 1) {
                    compute(index + 1);
                }
            }
        }

        vector<vector<int> > combine(int n, int k) {
            n_ = n;
            k_ = k;
            array_.resize(k);
            compute(0);
            return result_;
        }
    private:
        int n_;
        int k_;
        vector<int> array_;
        vector<vector<int> > result_;
};

int main()
{
    Solution s;
    vector<vector<int> > ret = s.combine(7, 3);
    printf("[\n");
    for (int i = 0; i < ret.size(); ++i) {
        printf(" [");
        for (int j = 0; j < ret[0].size(); ++j) {
            printf("%d,", ret[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");

    return 0;
}


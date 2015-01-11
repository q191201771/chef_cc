/**
 * Given a collection of numbers, return all possible permutations.
 * 
 * For example,
 *     [1,2,3] have the following permutations:
 *     [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
 */

class Solution {
    public:
        int valid(int index) {
            for (int i = 0; i < index; ++i) {
                if (array_[i] == array_[index]) {
                    return 0;
                }
            }
            return 1;
        }

        void compute(int index) {
            if (index == n_) {
                result_.push_back(array_);
                return;
            }

            for (int i = 0; i < n_; ++i) {
                array_[index] = num_[i];
                if (valid(index) == 1) {
                    compute(index + 1);
                }
            }
        }

        vector<vector<int> > permute(vector<int> &num) {
            n_ = num.size();
            num_ = num;
            array_.resize(n_);
            compute(0);
            return result_;
        }
    private:
        int n_;
        vector<int> num_;
        vector<int> array_;
        vector<vector<int> > result_;
};

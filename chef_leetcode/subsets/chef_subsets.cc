/**
 * Given a set of distinct integers, S, return all possible subsets.
 * 
 * Note:
 * Elements in a subset must be in non-descending order.
 * The solution set must not contain duplicate subsets.
 * For example,
 *     If S = [1,2,3], a solution is:
 * 
 *     [
 *       [3],
 *       [1],
 *       [2],
 *       [1,2,3],
 *       [1,3],
 *       [2,3],
 *       [1,2],
 *       []
 *     ]
 */

class Solution {
    public:
        void compute(int index) {
            if (index == vec_.size()) {
                return;
            }

            for (int i = index; i < vec_.size(); ++i) {
                sub_.push_back(vec_[i]);
                ret_.push_back(sub_);
                compute(i + 1);
                sub_.pop_back();
            }
        }

        vector<vector<int> > subsets(vector<int> &S) {
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


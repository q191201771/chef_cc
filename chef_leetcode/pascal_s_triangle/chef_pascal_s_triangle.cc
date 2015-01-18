/**
 * Given numRows, generate the first numRows of Pascal's triangle.
 * 
 * For example, given numRows = 5,
 *     Return
 * 
 *     [
 *      [1],
 *      [1,1],
 *      [1,2,1],
 *      [1,3,3,1],
 *      [1,4,6,4,1]
 *     ]
 */

class Solution {
    public:
        vector<vector<int> > generate(int numRows) {
            vector<vector<int> > ret;
            if (numRows <= 0) {
                return ret;
            }
            vector<int> sub;
            sub.push_back(1);
            ret.push_back(sub);
            for (int i = 1; i < numRows; ++i) {
                vector<int> sub;
                sub.push_back(1);
                for (int j = 1; j < i; ++j) {
                    sub.push_back(ret.back()[j - 1] + ret.back()[j]);
                }
                sub.push_back(1);
                ret.push_back(sub);
            }
            return ret;
        }
};

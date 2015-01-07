/**
 * Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
 * 
 * Follow up:
 * Did you use extra space?
 * A straight forward solution using O(mn) space is probably a bad idea.
 * A simple improvement uses O(m + n) space, but still not the best solution.
 * Could you devise a constant space solution?
 */

class Solution {
    public:
        void setZeroes(vector<vector<int> > &matrix) {
            setZeroes1(matrix);
        }

        /// O(m + n) space
        void setZeroes1(vector<vector<int> > &matrix) {
            int m = matrix.size();
            if (m < 1) {
                return;
            }
            int n = matrix[0].size();
            if (n < 1) {
                return;
            }

            vector<int> rows(m, 1);
            vector<int> columns(n, 1);

            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (matrix[i][j] == 0) {
                        rows[i] = 0;
                        columns[j] = 0; 
                    }
                }
            }

            for (int i = 0; i < m; ++i) {
                if (rows[i] == 0) {
                    for (int j = 0; j < n; ++j) {
                        matrix[i][j] = 0;
                    }
                }
            }
            for (int i = 0; i < n; ++i) {
                if (columns[i] == 0) {
                    for (int j = 0; j < m; ++j) {
                        matrix[j][i] = 0;
                    }
                }
            }
        }
};

/**
 * Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
 * 
 * Note: You can only move either down or right at any point in time.
 */

/// input: [[0]]         output: 0
/// intput [[1,2],[1,1]] output: 3
class Solution {
    public:
        int minPathSum(vector<vector<int> > &grid) {
            int m = grid.size();
            if (m < 1) {
                return 0;
            }
            int n = grid[0].size();
            if (n < 1) {
                return 0;
            }
            int **array = (int **)malloc(m * sizeof(int *));
            for (int i = 0; i < m; ++i) {
                array[i] = (int *)malloc(n * sizeof(int));
            }

            array[0][0] = grid[0][0];
            for (int i = 1; i < m; ++i) {
                array[i][0] = grid[i][0];
                array[i][0] += array[i - 1][0];
            }
            for (int i = 0; i < n; ++i) {
                array[0][i] = grid[0][i];
                array[0][i] += array[0][i - 1];
            }

            for (int i = 1; i < m; ++i) {
                for (int j = 1; j < n; ++j) {
                    array[i][j] = grid[i][j];
                    array[i][j] += array[i][j - 1] < array[i - 1][j] ? array[i][j - 1] : array[i - 1][j];
                }
            }
            int ret = array[m - 1][n - 1];

            for (int i = 0; i < m; ++i) {
                free(array[i]);
            }
            free(array);
            return ret;
        }
};

/**
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
 * 
 * The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 * 
 * How many possible unique paths are there?
 * 
 * Above is a 3 x 7 grid. How many possible unique paths are there?
 *
 * Note: m and n will be at most 100.
 */

/// input: 1,2 output: 1
class Solution {
    public:
        int uniquePaths(int m, int n) {
            if (m < 1 || n < 1) {
                return 0;
            }

            int **array = (int **)malloc(m * sizeof(int *));
            for (int i = 0; i < m; ++i) {
                array[i] = (int *)malloc(n * sizeof(int));
            }
            for (int i = 0; i < m; ++i) {
                array[i][0] = 1;
            }
            for (int i = 0; i < n; ++i) {
                array[0][i] = 1;
            }

            for (int i = 1; i < m; ++i) {
                for (int j = 1; j < n; ++j) {
                    array[i][j] = array[i - 1][j] + array[i][j - 1];
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


/**
 * Follow up for "Unique Paths":
 * 
 * Now consider if some obstacles are added to the grids. How many unique paths would there be?
 * 
 * An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 * 
 * For example,
 *     There is one obstacle in the middle of a 3x3 grid as illustrated below.
 * 
 *     [
 *       [0,0,0],
 *       [0,1,0],
 *       [0,0,0]
 *     ]
 * The total number of unique paths is 2.
 * 
 * Note: m and n will be at most 100.
 */

#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

/// input: [[1]]   output: 0
/// input: [[1,0]] output: 0
class Solution {
    public:
        int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
            int m = obstacleGrid.size();
            if (m < 1) {
                return 0;
            }
            int n = obstacleGrid[0].size();
            if (n < 1) { /// check all?
                return 0;
            }

            int **array = (int **)malloc(m * sizeof(int *));
            for (int i = 0; i < m; ++i) {
                array[i] = (int *)malloc(n * sizeof(int));
            }
            
            int tmp = 1;
            for (int i = 0; i < m; ++i) {
                if (obstacleGrid[i][0] == 1) {
                    tmp = 0;
                }
                array[i][0] = tmp;
            }
            tmp = 1;
            for (int i = 0; i < n; ++i) {
                if (obstacleGrid[0][i] == 1) {
                    tmp = 0;
                }
                array[0][i] = tmp;
            }

            for (int i = 1; i < m; ++i) {
                for (int j = 1; j < n; ++j) {
                    if (obstacleGrid[i][j] == 1) {
                        array[i][j] = 0;
                    } else {
                        array[i][j] = array[i - 1][j] + array[i][j - 1];
                    }
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

int main()
{
    Solution s;
    vector<vector<int> > vv;
    vector<int> v;
    v.push_back(1);
    v.push_back(0);
    vv.push_back(v);
    int ret = s.uniquePathsWithObstacles(vv);
    printf("ret=%d.\n", ret);
    return 0;
}

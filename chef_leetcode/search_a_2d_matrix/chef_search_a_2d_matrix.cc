/**
 * Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
 * 
 * Integers in each row are sorted from left to right.
 * The first integer of each row is greater than the last integer of the previous row.
 * For example,
 * 
 *     Consider the following matrix:
 * 
 *     [
 *       [1,   3,  5,  7],
 *       [10, 11, 16, 20],
 *       [23, 30, 34, 50]
 *     ]
 *     Given target = 3, return true.
 */

class Solution {
    public:
        bool searchMatrix(vector<vector<int> > &matrix, int target) {
            int row = matrix.size();
            if (row == 0) {
                return false;
            }
            int column = matrix[0].size();

            int small = 0;
            int big = row - 1;
            int mid;
            while (big >= small) {
                mid = (small + big) / 2;
                if (matrix[mid][0] > target) {
                    big = mid - 1;
                } else if (matrix[mid][0] < target) {
                    if (matrix[mid][column - 1] >= target || small == big) {
                        break;
                    }
                    small = mid + 1;
                } else {
                    return true;
                }
            }
            int r = mid;
            int left = 0;
            int right = column - 1;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (matrix[r][mid] > target) {
                    right = mid - 1;
                } else if (matrix[r][mid] < target) {
                    left = mid + 1;
                } else {
                    return true;
                }
            }
            return false;
        }
};

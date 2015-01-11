/**
 * Given an array of non-negative integers, you are initially positioned at the first index of the array.
 * 
 * Each element in the array represents your maximum jump length at that position.
 * 
 * Determine if you are able to reach the last index.
 *
 *
 * For example:
 * A = [2,3,1,1,4], return true.
 *
 * A = [3,2,1,0,4], return false.
 */

/// [1,1,2,2,0,1,1] true

class Solution {
    public:
        bool canJump(int A[], int n) {
            if (n < 0) {
                return false;
            }
            int max = 0;
            for (int i = 0; i <= max && i < n; ++i) {
                if (A[i] + i > max) {
                    max = A[i] + i;
                }
                if (max >= n - 1) {
                    return true;
                }
            }
            return false;
        }
};


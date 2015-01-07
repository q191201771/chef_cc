/**
 * Given an unsorted integer array, find the first missing positive integer.
 * 
 * For example,
 *   Given [1,2,0] return 3,
 *   and [3,4,-1,1] return 2.
 *
 *   Your algorithm should run in O(n) time and uses constant space.
 */

/// testcase
/// input: [0]   1 output: 1
/// input: [2,1] 2 output: 3
class Solution {
    public:
        int firstMissingPositive(int A[], int n) {
            int i = 0;
            for (; i < n; ++i) {
                while (A[i] > 0 && A[i] <= n && A[i] != i + 1) {
                    if (A[i] == A[A[i] - 1]) {
                        break;
                    }
                    int tmp = A[i];
                    A[i] = A[tmp - 1];
                    A[tmp - 1] = tmp;
                }
            }
            i = 0;
            for (; i < n; ++i) {
                if (i + 1 != A[i]) {
                    return i + 1;
                }
            }
            return n + 1;
        }
};


/**
 * Find the contiguous subarray within an array (containing at least one number)
 * which has the largest product.
 *
 * For example, given the array [2,3,-2,4],
 * the contiguous subarray [2,3] has the largest product = 6.
 */

class Solution {
    public:
        int maxProduct(int A[], int n) {
            if (n <= 0) {
                return -1;
            }
            int ret = A[0];
            int max_prod = A[0];
            int max_prev = A[0];
            int min_prod = A[0];
            int min_prev = A[0];
            for (int i = 1; i < n; ++i) {
                max_prod = max(max(min_prev * A[i], max_prev * A[i]), A[i]);
                min_prod = min(min(min_prev * A[i], max_prev * A[i]), A[i]);
                if (max_prod > ret) {
                    ret = max_prod;
                }
                max_prev = max_prod;
                min_prev = min_prod;
            }
            return ret;
        }
};


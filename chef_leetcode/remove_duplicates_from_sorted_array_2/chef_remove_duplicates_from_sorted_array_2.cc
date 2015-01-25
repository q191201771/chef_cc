/**
 * Follow up for "Remove Duplicates":
 * What if duplicates are allowed at most twice?
 * 
 * For example,
 *     Given sorted array A = [1,1,1,2,2,3],
 * 
 *     Your function should return length = 5, and A is now [1,1,2,2,3].
 */

class Solution {
    public:
        int removeDuplicates(int A[], int n) {
            if (n < 1) {
                return n;
            }
            int p = 0;
            int base = A[0];
            int count = 0;
            for (int i = 0; i < n; ++i) {
                if (A[i] == base) {
                    if (++count > 2) {
                        continue;
                    }
                } else {
                    base = A[i];
                    count = 1;
                }
                A[p++] = A[i];
            }
            return p;
        }
};



#include <assert.h>

/**
 * Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
 *
 * Do not allocate extra space for another array, you must do this in place with constant memory.
 *
 * For example,
 * Given input array A = [1,1,2],
 * 
 * Your function should return length = 2, and A is now [1,2].
 */

class Solution {
    public:
        int removeDuplicates(int A[], int n) {
            if (n <= 1) {
                return n;
            }
            int pos = 0;
            int save;
            for (int i = 0; i < n - 1; ++i) {
                if (A[i] != A[i + 1]) {
                    A[++pos] = A[i + 1];
                }               
            }
            return pos + 1;
        }
};

int main()
{
    Solution s;
    int A[1] = {1};
    int B[2] = {1, 1};
    int C[2] = {1, 2};
    int D[3] = {1, 1, 2};
    assert(s.removeDuplicates(A, 1) == 1);
    assert(s.removeDuplicates(B, 2) == 1);
    assert(s.removeDuplicates(C, 2) == 2);
    assert(s.removeDuplicates(D, 3) == 2);

    return 0;
}


/**
 * Given an array and a value, remove all instances of that value in place and
 * return the new length.
 *
 * The order of elements can be changed. It doesn't matter what you leave beyond
 * the new length.
 */

#include <assert.h>
#include <stdio.h>

class Solution {
    public:
        int removeElement(int A[], int n, int elem) {
            if (n <= 0) {
                return n;
            }
            int count = 0;
            for (int i = 0; i < n - count;) {
                if (A[i] == elem) {
                    int tmp = A[i];
                    A[i] = A[n - count - 1];
                    A[n - count - 1] = tmp;
                    ++count;
                } else {
                    ++i;
                }
            }
            return n - count;
        }
};

int main()
{
    Solution s;
    int A[2] = {4, 5};
    int B[2] = {3, 3};
    assert(s.removeElement(A, 2, 4) == 1);
    assert(s.removeElement(B, 2, 3) == 0);
    return 0;
}


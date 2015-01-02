/**
 * Given two sorted integer arrays A and B, merge B into A as one sorted array.
 *
 * Note:
 * You may assume that A has enough space (size that is greater or equal to m +
 * n) to hold additional elements from B. The number of elements initialized in
 * A and B are m and n respectively.
 */

#include <assert.h>

class Solution {
    public:
        void merge(int A[], int m, int B[], int n) {
            if (m == 0) {
                for (int i = 0; i < n; ++i) {
                    A[i] = B[i];
                }
                return;
            }
            if (n == 0) {
                return;
            }
            int feed = m + n - 1;
            int a = m - 1;
            int b = n - 1;
            for (; feed >= 0; --feed) {
                if (a < 0) {
                    A[feed] = B[b];
                    --b;
                    continue;
                }
                if (b < 0) {
                    A[feed] = A[a];
                    --a;
                    continue;
                }

                if (A[a] >= B[b]) {
                    A[feed] = A[a];
                    --a;
                    continue;
                }
                if (A[a] < B[b]) {
                    A[feed] = B[b];
                    --b;
                    continue;
                }
            }
        }
};

int main()
{
    Solution s;
    int A[1];
    int B[1] = {100};
    s.merge(A, 0, B, 1);
    assert(A[0] == 100);
    A[0] = 1;
    B[0] = 2;
    s.merge(A, 1, B, 1);
    assert(A[0] == 1);
    assert(A[1] == 2);
    return 0;
}


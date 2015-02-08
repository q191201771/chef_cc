/**
 * Implement int sqrt(int x).
 * 
 * Compute and return the square root of x.
 */

class Solution {
    public:
        int sqrt(int x) {
            if (x <= 0) {
                return 0;
            }

            int l = 0;
            int r = x / 2 + 1;
            int mid;
            for (; l <= r; ) {
                mid = (l + r) / 2;
                long long p = (long long)mid * (long long)mid;
                if (p == x) {
                    return mid;
                } else if (p < x) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            return r;
        }
};

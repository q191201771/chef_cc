/**
 * Implement pow(x, n).
 */

#include <stdio.h>

class Solution {
    public:
        double pow(double x, int n) {
            if (n == 0) {
                return 1.0f;
            }
            bool sign = n < 0;
            unsigned int m = sign ? -n : n;
            double ret = 1.0;
            while (m) {
                if (m & 1) {
                    ret *= x; 
                }
                m >>= 1;
                x *= x;
            }
            return sign ? 1 / ret : ret;
        }
};

int main()
{
    Solution s;
    printf("%lf\n", s.pow(1.00000, -2147483648));
    return 0;
}


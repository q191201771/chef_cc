/**
 * You are climbing a stair case. It takes n steps to reach to the top.
 * 
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 */

class Solution {
    public:
        int climbStairs(int n) {
            if (n <= 0) {
                return n;
            }
            if (n < 4) {
                return n;
            }
            int *arr = new int[n+1];
            arr[1] = 1;
            arr[2] = 2;
            int i = 3;
            for (; i <= n; ++i) {
                arr[i] = arr[i - 1] + arr[i - 2];
            }
            int ret = arr[n];
            delete []arr;
            return ret;
        }
};

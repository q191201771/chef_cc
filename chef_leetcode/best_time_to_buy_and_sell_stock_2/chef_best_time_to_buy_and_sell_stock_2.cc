/**
 * Say you have an array for which the ith element is the price of a given stock on day i.
 * Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
 */

class Solution {
    public:
        int maxProfit(vector<int> &prices) {
            if (prices.size() < 2) {
                return 0;
            }
            int ret = 0;
            int begin = 0;
            bool up = false;
            for (int i = 0; i < prices.size() - 1; ++i) {
                if (prices[i + 1] - prices[i] > 0) {
                    if (!up) {
                        begin = i;
                        up = true;
                    }
                } else {
                    if (up) {
                        up = false;
                        ret += prices[i] - prices[begin];
                    }
                }
            }
            if (up && begin != prices.size() - 1) {
                ret += prices[prices.size() - 1] - prices[begin];
            }

            return ret;
        }
};

/**
 * Say you have an array for which the ith element is the price of a given stock on day i.
 *
 * If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
 */

class Solution {
    public:
        int maxProfit(vector<int> &prices) {
            int ret = 0;
            if (prices.size() <= 1) {
                return ret;
            }
            
            int begin = 0, diff = 0;
            for (int i = 0; i < prices.size(); ++i) {
                diff = prices[i] - prices[begin];
                if (diff < 0) {
                    begin = i;
                }
                if (diff > ret) {
                    ret = diff;
                }
            }

            return ret;
        }
};

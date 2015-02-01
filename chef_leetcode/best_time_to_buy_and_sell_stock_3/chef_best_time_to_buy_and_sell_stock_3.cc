
class Solution {
    public:
        int maxProfit(vector<int> &prices) {
            if (prices.size() < 2) {
                return 0;
            }
            int ret = 0;
            int begin = 0;
            bool up = false;
            int profit[2] = {-1, -1};
            for (int i = 0; i < prices.size() - 1; ++i) {
                if (prices[i + 1] - prices[i] > 0) {
                    if (!up) {
                        begin = i;
                        up = true;
                    }
                } else {
                    if (up) {
                        up = false;
                        //ret += prices[i] - prices[begin];
                        int diff = prices[i] - prices[begin];
                        if (diff >= profit[1]) {
                            profit[0] = profit[1];
                            profit[1] = diff;
                        } else if (diff > profit[0]) {
                            profit[0] = diff;
                        }
                    }
                }
            }
            if (up && begin != prices.size() - 1) {
                //ret += prices[prices.size() - 1] - prices[begin];
                int diff = prices[prices.size() - 1] - prices[begin];
                if (diff >= profit[1]) {
                    profit[0] = profit[1];
                    profit[1] = diff;
                } else if (diff > profit[0]) {
                    profit[0] = diff;
                }
            }

            if (profit[1] == -1 && profit[0] == -1) {
                return 0;
            //} else if (profit[1] != -1 && profit[0] == -1) {
            //    return profit[1] * 2;
            } else if (profit[1] != -1 && profit[0] != -1) {
                return profit[0] + profit[1];
            }

            return ret;
        }
};

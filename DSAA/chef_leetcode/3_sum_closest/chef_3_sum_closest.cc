/**
 * Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
 * 
 *  For example, given array S = {-1 2 1 -4}, and target = 1.
 * 
 *  The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    public:
        int threeSumClosest(vector<int> &num, int target) {
            int diff = -1;
            int ret;
            if (num.size() < 3) {
                return ret;
            }
            sort(num.begin(), num.end());
            ret = num[0] + num[1] + num[2];
            diff = ret > target ? ret - target : target - ret;
            for (int i = 0; i < num.size() - 2; ++i) {
                int left = i + 1;
                int right = num.size() - 1;
                if (i > 0 && num[i] == num[i - 1]) {
                    continue;
                }
                while(left < right) {
                    int sum = num[i] + num[left] + num[right];
                    if (sum == target) {
                        return target;
                    } else if (sum < target) {
                        if (target - sum < diff) {
                            ret = sum;
                            diff = target - sum;
                        }
                        while(left < num.size() - 1 && num[left] == num[left + 1]) {
                            ++left;
                        }
                        ++left;
                    } else if (sum > target) {
                        if (sum - target < diff) {
                            ret = sum;
                            diff = sum - target;
                        }
                        while(right > 1 && num[right] == num[right - 1]) {
                            --right;
                        }
                        --right;
                    }
                }
            }
            return ret;
        }
};

int main() {
    Solution s;
    vector<int> vec;
    vec.push_back(0);
    vec.push_back(2);
    vec.push_back(1);
    vec.push_back(-3);
    int ret = s.threeSumClosest(vec, 1);
    printf("ret=%d.\n", ret);

    return 0;
}


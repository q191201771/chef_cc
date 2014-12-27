/**
 *
 * Given an array of integers, find two numbers such that they add up to a 
 * specific target number.
 *
 * The function twoSum should return indices of the two numbers such that they 
 * add up to the target, where index1 must be less than index2. Please note that 
 * your returned answers (both index1 and index2) are not zero-based.
 *
 * You may assume that each input would have exactly one solution.
 *
 * Input: numbers={2, 7, 11, 15}, target=9
 * Output: index1=1, index2=2
 *
 */

#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#include <stdio.h>

class Solution {
    public:
        vector<int> twoSum(vector<int> &numbers, int target) {
            vector<int> ret;
            map<int, int> map_;
            int i = 0;
            for (; i < numbers.size(); ++i) {
                if (map_.find(numbers[i]) == map_.end()) {
                    map_[target - numbers[i]] = i;
                } else {
                    ret.push_back((i < map_[numbers[i]] ? i : map_[numbers[i]]) + 1);
                    ret.push_back((i > map_[numbers[i]] ? i : map_[numbers[i]]) + 1);
                }
            }

            return ret;
        }
};

int main()
{
    vector<int> number;
    number.push_back(0);
    number.push_back(4);
    number.push_back(3);
    number.push_back(0);
    Solution s;
    vector<int> ret = s.twoSum(number, 0);
    if (ret.size() > 0) {
        printf("bingo, %d, %d\n", ret[0], ret[1]);
    }

    return 0;
}


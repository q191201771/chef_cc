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
using namespace std;
#include <stdio.h>

class Solution {
    public:
        vector<int> twoSum(vector<int> &numbers, int target) {
            vector<int> ret;
            vector<int> numbers_copy(numbers);
            sort(numbers_copy.begin(), numbers_copy.end());
            vector<int>::iterator i = numbers_copy.begin();
            vector<int>::iterator j = --numbers_copy.end();
            while(i != j) {
                if (*i + *j > target) {
                    --j;
                } else if (*i + *j < target) {
                    ++i;
                } else if (*i + *j == target) {
                    vector<int> ret;
                    vector<int>::iterator k = numbers.begin();
                    int i_pos,j_pos;
                    bool finded_i = false;
                    bool finded_j = false;
                    for (; k != numbers.end(); ++k) {
                        if (!finded_i && *k == *i) {
                            i_pos = k - numbers.begin() + 1;
                            finded_i = true;
                            if (finded_i && finded_j) {
                                break;
                            } else {
                                continue;
                            }
                        }
                        if (!finded_j && *k == *j) {
                            j_pos = k - numbers.begin() + 1;
                            finded_j = true;
                            if (finded_i && finded_j) {
                                break;
                            } else {
                                continue;
                            }
                        }
                    }
                    ret.push_back(i_pos < j_pos ? i_pos : j_pos);
                    ret.push_back(i_pos < j_pos ? j_pos : i_pos);
                    return ret;
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


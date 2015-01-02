/**
 * Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.
 * 
 * You may assume that the array is non-empty and the majority element always exist in the array.
 */

#include <stdio.h>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    public:
        int majorityElement(vector<int> &num) {
            int size = num.size();
            if (size < 1) {
                return -1;
            }
            sort(num.begin(), num.end());
            int key = num[0];
            int count = 0;
            for (int i = 0; i < size; ++i) {
                if (key == num[i]) {
                    if (++count > size/2) {
                        return key;
                    }
                } else {
                    key = num[i];
                }
            }
            return -1;
        }
};

int main()
{
    Solution s;
    vector<int> vec;
    vec.push_back(1);
    int ret = s.majorityElement(vec);
    assert(ret == 1);
    vec.clear();
    vec.push_back(-1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(1);
    ret = s.majorityElement(vec);
    assert(ret == 1);
    return 0;
}


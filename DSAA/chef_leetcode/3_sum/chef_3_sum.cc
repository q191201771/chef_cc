/**
 * Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
 * 
 * Note:
 * Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
 *     The solution set must not contain duplicate triplets.
 *     For example, given array S = {-1 0 1 2 -1 -4},
 * 
 *     A solution set is:
 *     (-1, 0, 1)
 *     (-1, -1, 2)
 */

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    public:
        vector<vector<int> > threeSum(vector<int> &num) {
            vector<vector<int> > ret;
            if (num.size() < 3) {
                return ret;
            }
            sort(num.begin(), num.end());
            for (int i = 0; i < num.size() - 2; ++i) {
                int left = i + 1;
                int right = num.size() - 1;
                if (i > 0 && num[i] == num[i - 1]) {
                    continue;
                }
                while(left < right) {
                    int sum = num[i] + num[left] + num[right];
                    if (sum == 0) {
                        vector<int> vec;
                        vec.push_back(num[i]);
                        vec.push_back(num[left]);
                        vec.push_back(num[right]);
                        ret.push_back(vec);

                        while(left < num.size() - 1 && num[left] == num[left + 1]) {
                            ++left;
                        }
                        while(right > 1 && num[right] == num[right - 1]) {
                            --right;
                        }
                        ++left;
                        --right;
                    } else if (sum < 0) {
                        while(left < num.size() - 1 && num[left] == num[left + 1]) {
                            ++left;
                        }
                        ++left;
                    } else if (sum > 0) {
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

void print_vec_vec_int(vector<vector<int> > &val) {
    printf("-----\n");
    for (int i = 0; i < val.size(); ++i) {
        printf("{");
        for (int j = 0; j < val[i].size(); ++j) {
            printf("%d ", val[i][j]);
        }
        printf("}\n");
    }
    printf("-----\n");
}

int main() {
    Solution s;
    vector<int> vec;
//    vec.push_back(-1);
//    vec.push_back(0);
//    vec.push_back(1);
//    vec.push_back(2);
//    vec.push_back(-1);
//    vec.push_back(-4);
    vec.push_back(-2);
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(2);
    vector<vector<int> > ret = s.threeSum(vec);
    print_vec_vec_int(ret);

    return 0;
}


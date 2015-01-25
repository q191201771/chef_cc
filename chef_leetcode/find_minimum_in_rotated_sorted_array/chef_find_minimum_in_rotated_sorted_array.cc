/**
 * Suppose a sorted array is rotated at some pivot unknown to you beforehand.
 *
 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 *
 * Find the minimum element.
 *
 * You may assume no duplicate exists in the array.
 */

#include <stdio.h>
#include <vector>
using namespace std;

class Solution {
    public:
        int findMin(vector<int> &num) {
            int size = num.size();
            if (size == 0) {
                return -1;
            }
            int low = 0;
            int high = size - 1;

            while(low + 1 < high) {
                int mid = (low + high) / 2;
                if (num[low] <= num[mid] && num[mid] <= num[high]) {
                    return num[low];
                }
                if (num[low] > num[mid]) {
                    high = mid;
                    continue;
                }
                if (num[high] < num[mid]) {
                    low = mid;
                    continue;
                }
            }
            if (low == high) {
                return num[low];
            } else {
                return num[low] < num[high] ? num[low] : num[high];
            }
        }
};

int main()
{
    Solution s;
    int arr[] = {2, 3, 4, 5, 1};
    vector<int> vec(arr, arr + 5);
    s.findMin(vec);

    return 0;
}

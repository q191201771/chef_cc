/**
 * Given a sorted array of integers, find the starting and ending position of a given target value.
 * 
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * 
 * If the target is not found in the array, return [-1, -1].
 * 
 * For example,
 *     Given [5, 7, 7, 8, 8, 10] and target value 8,
 *     return [3, 4].
 */

#include <stdio.h>
#include <vector>
using namespace std;

int binary_search(int arr[], int left, int right, int target);

class Solution {
    public:
        vector<int> searchRange(int A[], int n, int target) {
            vector<int> ret;
            int pos = binary_search(A, 0, n - 1, target);
            if (pos == -1) {
                ret.push_back(-1);
                ret.push_back(-1);
                return ret;
            }
            int l = -1;
            int pos2 = pos - 1;
            for (; pos2 >= 0; ) {
                int a = binary_search(A, 0, pos2, target);
                if (a != -1) {
                    l = a;
                    pos2 = a - 1;
                } else {
                    break;
                }
            }
            int r = -1;
            pos2 = pos + 1;
            for (; pos2 <= n - 1; ) {
                int a = binary_search(A, pos2, n - 1, target);
                if (a != -1) {
                    r = a;
                    pos2 = a + 1;
                } else {
                    break;
                }
            }
            ret.push_back(l == -1 ? pos : l);
            ret.push_back(r == -1 ? pos : r);
            return ret;
        }
};

int binary_search(int arr[], int left, int right, int target)
{
    for (; left <= right; ) {
        int mid = (left + right) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else if (arr[mid] > target) {
            right = mid - 1;
        }
    }
    return -1;
}

int main()
{
    int arr[] = {2, 2};
    Solution s;
    vector<int> vec = s.searchRange(arr, 2, 2);
    printf("ret:%d %d\n", vec[0], vec[1]);

    return 0;
}


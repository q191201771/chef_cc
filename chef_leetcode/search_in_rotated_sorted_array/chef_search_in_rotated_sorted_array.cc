/**
 * Suppose a sorted array is rotated at some pivot unknown to you beforehand.
 * 
 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 * 
 * You are given a target value to search. If found in the array return its index, otherwise return -1.
 * 
 * You may assume no duplicate exists in the array.
 */

/// [4 5 6 7 8 1 2 3], 8
/// [3 1] 1
/// [1]   0
/// [5 1 3] 3
class Solution {
    public:
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
      
        int search(int A[], int n, int target) {
            int ret = -1;
            if (n < 1) {
                return ret;
            }
            int left = 0;
            int right = n - 1;
            for (; left <= right; ) {
                int mid = (left + right) / 2;
                if (A[left] <= A[mid]) {
                    if ((ret = binary_search(A, left, mid, target)) != -1) {
                        return ret;
                    }
                    left = mid + 1;
                    continue;
                } 
                if (A[right] >= A[mid]) {
                    if ((ret = binary_search(A, mid, right, target)) != -1) {
                        return ret;
                    }
                    right = mid - 1;
                    continue;
                }

                if (A[left] > A[mid]) {
                    if (left + 1 == mid) {
                        if (A[left] == target) {
                            return left;
                        }
                        if (A[mid] == target) {
                            return mid;
                        }
                        break;
                    }
                } 
                if (A[right] < A[mid]) {
                    if (mid + 1 == right) {
                        if (A[mid] == target) {
                            return mid;
                        }
                        if (A[right] == target) {
                            return right;
                        }
                        break;
                    }
                }
            }
            return -1;
        }
};


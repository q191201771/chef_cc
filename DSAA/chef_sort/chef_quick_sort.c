#include "chef_quick_sort.h"

void chef_quick_sort(int arr[], int left, int right)
{
    if (left >= right) {
        return;
    }
    int begin = left;
    int end = right;
    int key = arr[left];
    while (begin < end) {
        while(begin < end && arr[end] > key) {
            --end;
        }
        arr[begin] = arr[end];
        while(begin < end && arr[begin] < key) {
            ++begin;
        }
        arr[end] = arr[begin];
    }
    arr[begin] = key;
    chef_quick_sort(arr, left, begin - 1);
    chef_quick_sort(arr, begin + 1, right);
}


#include "chef_buddle_sort.h"

void chef_buddle_sort(int arr[], int size) 
{
    int i, j, bak;
    j = size - 1;
    for (; j > 0; --j) {
        i = 0;
        for (; i < j; ++i) {
            if (arr[i] > arr[i + 1]) {
                /// swap
                bak = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = bak;
            } 
        }
    }
}


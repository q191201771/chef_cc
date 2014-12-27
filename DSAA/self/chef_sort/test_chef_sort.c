#include "chef_buddle_sort.h"
#include "chef_quick_sort.h"
#include <stdio.h>

void print_arr(int arr[], int size)
{
    printf("\n");
    int i = 0;
    for (; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void TEST_BUDDLE_SORT()
{
    printf(">TEST_BUDDLE_SORT.\n");
    int arr1[] = {20, 40, 60, 80, 30, 70, 90, 10, 50, 0};
    int size1 = sizeof(arr1) / sizeof(int);
    int arr2[] = {23, 44, 66, 76, 98, 11, 3, 9, 7};
    int size2 = sizeof(arr2) / sizeof(int);
    int arr3[] = {95, 45, 15, 78, 84, 51, 24, 12};
    int size3 = sizeof(arr3) / sizeof(int);
    int arr4[] = {0};
    int arr5[] = {1, 0};
    chef_buddle_sort(arr1, size1);
    print_arr(arr1, size1);
    chef_buddle_sort(arr2, size2);
    print_arr(arr2, size2);
    chef_buddle_sort(arr3, size3);
    print_arr(arr3, size3);
    chef_buddle_sort(arr4, 1);
    print_arr(arr4, 1);
    chef_buddle_sort(arr5, 2);
    print_arr(arr5, 2);
    printf("<TEST_BUDDLE_SORT.\n");
}

void TEST_QUICK_SORT()
{
    printf(">TEST_QUICK_SORT.\n");
    int arr1[] = {20, 40, 60, 80, 30, 70, 90, 10, 50, 0};
    int size1 = sizeof(arr1) / sizeof(int);
    int arr2[] = {23, 44, 66, 76, 98, 11, 3, 9, 7};
    int size2 = sizeof(arr2) / sizeof(int);
    int arr3[] = {95, 45, 15, 78, 84, 51, 24, 12};
    int size3 = sizeof(arr3) / sizeof(int);
    int arr4[] = {0};
    int arr5[] = {1, 0};
    chef_quick_sort(arr1, 0, size1 - 1);
    print_arr(arr1, size1);
    chef_quick_sort(arr2, 0, size2 - 1);
    print_arr(arr2, size2);
    chef_quick_sort(arr3, 0, size3 - 1);
    print_arr(arr3, size3);
    chef_quick_sort(arr4, 0, 0);
    print_arr(arr4, 1);
    chef_quick_sort(arr5, 0, 1);
    print_arr(arr5, 2);
    printf("<TEST_QUICK_SORT.\n");
}

int main(int argc, char **argv)
{
    printf(">test_sort.\n");
    TEST_BUDDLE_SORT();
    TEST_QUICK_SORT();
    printf("<test_sort.\n");
    return 0;
}


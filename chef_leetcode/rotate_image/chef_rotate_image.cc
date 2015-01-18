/**
 * You are given an n x n 2D matrix representing an image.
 * 
 * Rotate the image by 90 degrees (clockwise).
 * 
 * Follow up:
 * Could you do this in-place?
 */

#include <stdio.h>
#include <vector>
using namespace std;

class Solution {
    public:
        void rotate(vector<vector<int> > &matrix) {
            int n = matrix.size();
            if (n == 0) {
                return;
            }
            /// TODO check if matrix
            
            for (int count = 0; count < n / 2; ++count) {
                int begin = count;
                int end = n - 1 - count;
                for (int i = 0; i < end - begin; ++i) {
                    int tmp;
                    tmp = matrix[end - i][begin];
                    matrix[end - i][begin] = matrix[end][end - i];
                    matrix[end][end - i] = matrix[begin + i][end];
                    matrix[begin + i][end] = matrix[begin][begin + i];
                    matrix[begin][begin + i] = tmp;
                }
            }
        }
};

int main()
{
    vector<vector<int> > matrix;
    vector<int> sub;
    sub.clear();
    sub.push_back(1);
    sub.push_back(2);
    sub.push_back(3);
    matrix.push_back(sub);
    sub.clear();
    sub.push_back(4);
    sub.push_back(5);
    sub.push_back(6);
    matrix.push_back(sub);
    sub.clear();
    sub.push_back(7);
    sub.push_back(8);
    sub.push_back(9);
    matrix.push_back(sub);
    Solution s;
    s.rotate(matrix);
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

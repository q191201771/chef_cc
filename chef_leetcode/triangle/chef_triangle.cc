/**
 * Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.
 * 
 * For example, given the following triangle
 * [
 *  [2],
 *  [3,4],
 *  [6,5,7],
 *  [4,1,8,3]
 * ]
 * The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
 * 
 * Note:
 * Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
 */

#include <stdio.h>
#include <vector>
using namespace std;

class Solution {
    public:
        int min(int a, int b) {
            return a < b ? a : b;
        }

        int minimumTotal(vector<vector<int> > &triangle) {
            if (triangle.size() == 0) {
                return -1;
            }
            for (int i = 1; i < triangle.size(); ++i) {
                triangle[i][0] += triangle[i - 1][0];
                triangle[i][i] += triangle[i - 1][i - 1];
                for (int j = 1; j < i; ++j) {
                    triangle[i][j] += min(triangle[i - 1][j - 1], triangle[i - 1][j]);
                }
            }
            
            int min = triangle[triangle.size() - 1][0];
            for (int i = 1; i < triangle[triangle.size() - 1].size(); ++i) {
                if (triangle[triangle.size() - 1][i] < min) {
                    min = triangle[triangle.size() - 1][i];
                }
            }
            return min;
        }
};

void print(vector<vector<int> > vec) {
    printf("-----\n");
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            printf("%d ", vec[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    Solution s;
    vector<int> sub;
    vector<vector<int> > vec;
    sub.clear();
    sub.push_back(2);
    vec.push_back(sub);
    sub.clear();
    sub.push_back(3);
    sub.push_back(4);
    vec.push_back(sub);
    sub.clear();
    sub.push_back(6);
    sub.push_back(5);
    sub.push_back(7);
    vec.push_back(sub);
    sub.clear();
    sub.push_back(4);
    sub.push_back(1);
    sub.push_back(8);
    sub.push_back(3);
    vec.push_back(sub);
    print(vec);
    printf("%d.\n", s.minimumTotal(vec));
    print(vec);

    return 0;
}

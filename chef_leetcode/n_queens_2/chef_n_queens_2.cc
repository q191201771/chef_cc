/**
 * Follow up for N-Queens problem.
 *
 * Now, instead outputting board configurations, return the total number of
 * distinct solutions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

class Solution {
    public:
        int diff(int x, int y) {
            return x > y ? x - y : y - x;
        }

        int succ(int index) {
            for (int i = 1; i < index; ++i) {
                if (array_[index] == array_[i] || (diff(index, i) == diff(array_[index], array_[i]))) {
                    return 0;
                }
            }
            return 1;
        }

        void solve_n_queens(int index) {
            if (index > n_) {
                ++count_;
                return;
            }

            for (int i = 1; i <= n_; ++i) {
                array_[index] = i;
                if (succ(index)) {
                    solve_n_queens(index + 1);
                }
            }
        }

        int totalNQueens(int n) {
            n_ = n;
            count_ = 0;
            array_.resize(n + 1, 0);
            solve_n_queens(1);
            return count_;
        }

    private:
        int n_;
        vector<int> array_; 
        int count_;
};


int main(int argc, char **argv) {
    int i = 8;
    if (argc == 2) {
        i = atoi(argv[1]);
    }
    Solution s;
    //for (int i = 0; i < 9; ++i) {
    int ret = s.totalNQueens(i);
    printf("%d size:%d.\n", i, ret);
    //}
    return 0;
}


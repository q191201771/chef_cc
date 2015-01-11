/**
 * The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
 * 
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 * 
 * Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.
 * 
 * For example,
 *     There exist two distinct solutions to the 4-queens puzzle:
 * 
 *     [
 *      [".Q..",  // Solution 1
 *       "...Q",
 *       "Q...",
 *       "..Q."],
 * 
 *      ["..Q.",  // Solution 2
 *       "Q...",
 *       "...Q",
 *       ".Q.."]
 *     ]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

void print_solves(vector<vector<string> > &vec) {
    printf("[\n");
    for (int i = 0; i < vec.size(); ++i) {
        printf(" [\n");
        for (int j = 0; j < vec[i].size(); ++j) {
            printf("%s\n", vec[i][j].c_str());
        }
        printf(" ]\n");
    }
    printf("]\n");
}


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
                vector<string> vec;
                for (int i = 0; i < n_; ++i) {
                    string str(n_, '.');
                    str[array_[i + 1] - 1] = 'Q';
                    vec.push_back(str);
                }
                result_.push_back(vec);
                return;
            }

            for (int i = 1; i <= n_; ++i) {
                array_[index] = i;
                if (succ(index)) {
                    solve_n_queens(index + 1);
                }
            }
        }

        vector<vector<string> > solveNQueens(int n) {
            n_ = n;
            array_.resize(n + 1, 0);
            solve_n_queens(1);
            return result_;
        }

    private:
        int n_;
        vector<int> array_; 
        vector<vector<string> > result_;
};


int main(int argc, char **argv) {
    int i = 8;
    if (argc == 2) {
        i = atoi(argv[1]);
    }
    Solution s;
    //for (int i = 0; i < 9; ++i) {
    vector<vector<string> > ret = s.solveNQueens(i);
    printf("%d size:%d.\n", i, ret.size());
    //}
    print_solves(ret);
    return 0;
}


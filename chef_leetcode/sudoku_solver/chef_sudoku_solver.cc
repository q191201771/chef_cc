/**
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 * 
 * Empty cells are indicated by the character '.'.
 * 
 * You may assume that there will be only one unique solution.
 */

#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

class Solution {
    public:
        void boundary(int val, int &left, int &right) {
            if (val == 0 || val == 1 || val == 2) {
                left = 0;right = 2;
            } else if (val == 3 || val == 4 || val == 5) {
                left = 3;right = 5;
            } else {
                left = 6;right = 8;
            }
        }

        bool valid(int index) {
            char val = (*board_)[ys_[index]][xs_[index]];
            for (int i = 0; i < 9; ++i) {
                if (i != xs_[index] && val == (*board_)[ys_[index]][i]) {
                    return false;
                }
                if (i != ys_[index] && val == (*board_)[i][xs_[index]]) {
                    return false;
                }
            }
            int xleft, xright, yleft, yright;
            boundary(ys_[index], yleft, yright);
            boundary(xs_[index], xleft, xright);
            for (int i = yleft; i <= yright; ++i) {
                for (int j = xleft; j <= xright; ++j) {
                    if ((i == ys_[index] || j == xs_[index]) || (*board_)[i][j] == '.') {
                        continue;
                    }
                    if (val == (*board_)[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool compute(int index) {
            if (index == xs_.size()) {
                return true;
            }

            for (int i = 1; i < 10; ++i) {
                (*board_)[ys_[index]][xs_[index]] = i + '0';
                if (valid(index)) {
                    if (compute(index + 1)) {
                        return true;
                    }
                }
            }
            (*board_)[ys_[index]][xs_[index]] = '*';
            return false;
        }

        void solveSudoku(vector<vector<char> > &board) {
            board_ = &board;
            for (int i = 0; i < board.size(); ++i) {
                for (int j = 0; j < board[0].size(); ++j) {
                    if (board[i][j] == '.') {
                        ys_.push_back(i);
                        xs_.push_back(j);
                    }
                }
            }
            if (xs_.size() == 0) {
                return;
            }
            compute(0);
        }
    private:
        vector<vector<char> > *board_;
        vector<int> xs_;
        vector<int> ys_;
};

int main()
{
    Solution s;
    char arr[9];
    vector<vector<char> > board;
    vector<char> sub;
    memcpy(arr, "..9748...", 9);
    sub.clear();
    for (int i = 0; i < 9; ++i) {
        sub.push_back(arr[i]);
    }
    board.push_back(sub);
    memcpy(arr, "7........", 9);
    sub.clear();
    for (int i = 0; i < 9; ++i) {
        sub.push_back(arr[i]);
    }
    board.push_back(sub);
    memcpy(arr, ".2.1.9...", 9);
    sub.clear();
    for (int i = 0; i < 9; ++i) {
        sub.push_back(arr[i]);
    }
    board.push_back(sub);
    memcpy(arr, "..7...24.", 9);
    sub.clear();
    for (int i = 0; i < 9; ++i) {
        sub.push_back(arr[i]);
    }
    board.push_back(sub);
    memcpy(arr, ".64.1.59.", 9);
    sub.clear();
    for (int i = 0; i < 9; ++i) {
        sub.push_back(arr[i]);
    }
    board.push_back(sub);
    memcpy(arr, ".98...3..", 9);
    sub.clear();
    for (int i = 0; i < 9; ++i) {
        sub.push_back(arr[i]);
    }
    board.push_back(sub);
    memcpy(arr, "...8.3.2.", 9);
    sub.clear();
    for (int i = 0; i < 9; ++i) {
        sub.push_back(arr[i]);
    }
    board.push_back(sub);
    memcpy(arr, "........6", 9);
    sub.clear();
    for (int i = 0; i < 9; ++i) {
        sub.push_back(arr[i]);
    }
    board.push_back(sub);
    memcpy(arr, "...2759..", 9);
    sub.clear();
    for (int i = 0; i < 9; ++i) {
        sub.push_back(arr[i]);
    }
    board.push_back(sub);
    s.solveSudoku(board);
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}


/**
 * Given a 2D board and a word, find if the word exists in the grid.
 * 
 * The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.
 * 
 * For example,
 *     Given board =
 * 
 *     [
 *       ["ABCE"],
 *       ["SFCS"],
 *       ["ADEE"]
 *     ]
 *     word = "ABCCED", -> returns true,
 *     word = "SEE", -> returns true,
 *     word = "ABCB", -> returns false.
 */

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

class Solution {
    public:

        struct position {
            position(int i, int j) : i_(i), j_(j) { }
            int i_;
            int j_;
        };

        bool valid(int i, int j) {
            for (int k = 0; k < used_pos_.size(); ++k) {
                if (used_pos_[k].i_ == i && used_pos_[k].j_ == j) {
                    return false;
                }
            }
            return true;
        }
        bool erase(int i, int j) {
            vector<position>::iterator iter = used_pos_.begin();
            for (; iter != used_pos_.end(); ++iter) {
                if (iter->i_ == i && iter->j_ == j) {
                    used_pos_.erase(iter);
                    break;
                }
            }
        }

        bool compute(int i, int j) {
            if (board_[i][j] != word_[match_count_]) {
                return false;
            }
            if (++match_count_ == word_.size()) {
                return true;
            }
            used_pos_.push_back(position(i, j));
            if (i > 0 && valid(i - 1, j)) {
                if (compute(i - 1, j)) {
                    return true;
                }
            }
            if (i != row_ - 1 && valid(i + 1, j)) {
                if (compute(i + 1, j)) {
                    return true;
                }
            }
            if (j > 0 && valid(i, j - 1)) {
                if (compute(i, j - 1)) {
                    return true;
                }
            }
            if (j != column_ - 1 && valid(i, j + 1)) {
                if (compute(i, j + 1)) {
                    return true;
                }
            }
            --match_count_;
            erase(i, j);
            return false;
        }
        bool exist(vector<vector<char> > &board, string word) {
            if (board.size() == 0) {
                return false;
            }
            board_ = board;
            word_ = word;
            match_count_ = 0;
            row_ = board_.size();
            column_ = board_[0].size();
            int i = 0;
            for (; i < row_; ++i) {
                int j = 0;
                for (; j < column_; ++j) {
                    if (compute(i, j)) {
                        return true;
                    }
                }
            }
            return false;
        }
    private:
        vector<vector<char> > board_;
        string word_;
        int match_count_;
        vector<position> used_pos_;
        int row_;
        int column_;
};

int main()
{
    vector<vector<char> > board;
    vector<char> sub;
    sub.push_back('a');
    sub.push_back('b');
    board.push_back(sub);
    sub.clear();
    sub.push_back('c');
    sub.push_back('d');
    board.push_back(sub);
    string word = "acdb";
    Solution s;
    printf("%s.\n", s.exist(board, word) ? "true" : "false");

    return 0;
}


/**
 * Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
 * 
 * The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
 * 
 * Note:
 * A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.
 */

class Solution {
    public:
        bool isValidSudoku(vector<vector<char> > &board) {
            if (board.size() != 9 || board[0].size() != 9) { /// && [1] [2] ...
                return false;
            }
            set<char> filled_set;
            for (int i = 0; i < 9; ++i) {
                filled_set.clear();
                for (int j = 0; j < 9; ++j) {
                    if (board[i][j] == '.') {
                        continue;
                    }
                    if (filled_set.find(board[i][j]) != filled_set.end()) {
                        return false;
                    }
                    filled_set.insert(board[i][j]);
                }
                filled_set.clear();
                for (int k = 0; k < 9; ++k) {
                    if (board[k][i] == '.') {
                        continue;
                    }
                    if (filled_set.find(board[k][i]) != filled_set.end()) {
                        return false;
                    }
                    filled_set.insert(board[k][i]);
                }
            }
            for (int i = 0; i < 7; i += 3) {
                for (int j = 0; j < 7; j += 3) {
                    filled_set.clear();
                    for (int m = i; m < 3 + i; ++m) {
                        for (int n = j; n < 3 + j; ++n) {
                            if (board[m][nj] == '.') {
                                continue;
                            }
                            if (filled_set.find(board[m][n]) != filled_set.end()) {
                                return false;
                            }
                            filled_set.insert(board[m][n]);
                        }
                    }
                }
            }
            return true;
        }
};

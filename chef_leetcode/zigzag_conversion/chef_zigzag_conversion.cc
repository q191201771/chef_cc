/**
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)
 * 
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * And then read line by line: "PAHNAPLSIIGYIR"
 * Write the code that will take a string and make this conversion given a number of rows:
 * 
 * string convert(string text, int nRows);
 * convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
 */

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

class Solution {
    public:
        string convert(string s, int nRows) {
            if (nRows < 2 || s.length() <= nRows) {
                return s;
            }
            vector<string> strs(nRows); 
            int row = 0;
            int step = 1;
            for (int i = 0; i < s.length(); ++i) {
                if (row == nRows - 1) {
                    step = -1;
                } else if (row == 0) {
                    step = 1;
                }
                strs[row] += s[i];
                row += step;
            }
            string ret;
            for (int i = 0; i < strs.size(); ++i) {
                ret += strs[i];
            }

            return ret;
        }
};

int main()
{
    Solution s;
    printf("%s\n", s.convert("abcd", 2).c_str());
    return 0;
}


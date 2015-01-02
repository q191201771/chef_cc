/**
 * Given two binary strings, return their sum (also a binary string).
 *
 * For example,
 * a = "11"
 * b = "1"
 * Return "100".
 */

#include <assert.h>
#include <stdio.h>
#include <string>
using namespace std;

class Solution {
    public:
        string addBinary(string a, string b) {
            string ret;
            string::reverse_iterator iterA = a.rbegin();
            string::reverse_iterator iterB = b.rbegin();
            bool addExtend = false;
            while(iterA != a.rend() || iterB != b.rend()) {
                char ch = 0;
                if (iterA != a.rend()) {
                    ch += *iterA - '0';
                    ++iterA;
                }
                if (iterB != b.rend()) {
                    ch += *iterB - '0';
                    ++iterB;
                }
                if (addExtend) {
                    ch += 1;
                }
                if (ch > 1) {
                    addExtend = true;
                    ch -= 2;
                } else {
                    addExtend = false;
                }
                ch += '0';
                ret.insert(0, 1, ch);
            }
            if (addExtend) {
                ret.insert(0, 1, '1');
            }
            return ret;
        }
};

int main()
{
    Solution s;
    assert(s.addBinary("0", "0") == "0");
    assert(s.addBinary("11", "1") == "100");
    assert(s.addBinary("1010", "1011") == "10101");

    return 0;
}


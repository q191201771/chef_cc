/**
 * Given a positive integer, return its corresponding column title as appear in an Excel sheet.
 * 
 * For example:
 *
 *   1 -> A
 *   2 -> B
 *   3 -> C
 *   ...
 *   26 -> Z
 *   27 -> AA
 *   28 -> AB 
 */

#include <stdio.h>
#include <assert.h>
#include <string>
using namespace std;

class Solution {
    public:
        string convertToTitle(int n) {
            string ret;
            int m;
            for (; n != 0; ) {
                m = (n - 1) % 26;
                ret.insert(0, 1, (char)(m + 'A'));
                n -= m;
                n /= 26;
            }
            return ret;
        }
};

int main()
{
    Solution s;
    int n;
    string ret;
    n = 1;
    ret = s.convertToTitle(n);
    assert(ret == "A");
    n = 25;
    ret = s.convertToTitle(n);
    assert(ret == "Y");
    n = 26;
    ret = s.convertToTitle(n);
    assert(ret == "Z");
    n = 27;
    ret = s.convertToTitle(n);
    assert(ret == "AA");
    n = 28;
    ret = s.convertToTitle(n);
    assert(ret == "AB");

    return 0;
}


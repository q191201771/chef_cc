/**
 * Given a column title as appear in an Excel sheet, return its corresponding column number.
 *
 * For example:
 *
 *    A -> 1
 *    B -> 2
 *    C -> 3
 *     ...
 *    Z -> 26
 *   AA -> 27
 *   AB -> 28 
 */

#include <assert.h>
#include <math.h>
#include <string>
using namespace std;

class Solution {
    public:
        int titleToNumber(string s) {
            int ret = 0;
            string::reverse_iterator iter = s.rbegin();
            int i = 0;
            for (; iter != s.rend(); ++iter) {
                ret += (*iter - 'A' + 1) * pow(26, i++);
            }
            return ret;
        }
};

int main()
{
    Solution s;
    assert(s.titleToNumber(string("A"))== 1);

    return 0;
}


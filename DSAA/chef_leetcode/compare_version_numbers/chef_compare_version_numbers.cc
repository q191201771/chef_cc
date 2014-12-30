/**
 * Compare two version numbers version1 and version1.
 * If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.
 *
 * You may assume that the version strings are non-empty and contain only digits and the . character.
 * The . character does not represent a decimal point and is used to separate number sequences.
 * For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.
 * 
 * Here is an example of version numbers ordering:
 * 
 * 0.1 < 1.1 < 1.2 < 13.37
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string>
using namespace std;

class Solution {
    public:
        int compareVersion(string version1, string version2) {
            int num1;
            int num2;
            std::size_t pos1 = 0;
            std::size_t pos2 = 0;
            bool iBreak = false;
            bool out1 = false;
            bool out2 = false;
            rtrim(version1);
            rtrim(version2);

            for (; !iBreak; ) {
                version1 = version1.substr(pos1);
                pos1 = version1.find('.');
                if (pos1 == string::npos) {
                    num1 = atoi(version1.c_str());
                    out1 = true;
                } else {
                    num1 = atoi(version1.substr(0, pos1).c_str());
                    ++pos1;
                }

                version2 = version2.substr(pos2);
                pos2 = version2.find('.');
                if (pos2 == string::npos) {
                    num2 = atoi(version2.c_str());
                    out2 = true;
                } else {
                    num2 = atoi(version2.substr(0, pos2).c_str());
                    ++pos2;
                }

                if (num1 > num2) {
                    return 1;
                } else if (num1 < num2) {
                    return -1;
                }
                if (out1 && !out2) {
                    return -1;
                } else if (!out1 && out2) {
                    return 1;
                } else if (out1 && out2) {
                    return 0;
                }
            }
            return 0;
        }
    private:
        void rtrim(string &str) {
            if (str.length() < 1) {
                return;
            }
            int i = str.length() - 1;
            bool spot = false;
            int j = i;
            for (; i >= 0; --i) {
                if (str[i] == '0') {
                    continue;
                } else if (str[i] == '.') {
                    j = i - 1;
                } else {
                    break;
                }
            }
            str = str.substr(0, j + 1);
        }
};

int main()
{
    Solution s;
    int ret;
    assert(s.compareVersion("1", "0") == 1);
    assert(s.compareVersion("0", "1") == -1);
    assert(s.compareVersion("1", "1.1") == -1);
    assert(s.compareVersion("0.1", "0.0.1") == 1);
    assert(s.compareVersion("1.0", "1") == 0);
    assert(s.compareVersion("1.0", "1.0") == 0);
    assert(s.compareVersion("19.8.3.17.5.01.0.0.4.0.0.0.0.0.0.0.0.0.0.0.0.0.00.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.000000.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.000000", "19.8.3.17.5.01.0.0.4.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0000.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.000000") == 0);
    assert(s.compareVersion("1.1", "1.10") == -1);
    return 0;
}


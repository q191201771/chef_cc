/**
 * Write a function to find the longest common prefix string amongst an array of
 * strings.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
    public:
        string longestCommonPrefix(vector<string> &strs) {
            string ret;
            if (strs.size() <= 0) {
                return ret;
            }
            for (int i = 1; i <= strs[0].length(); ++i) {
                string sub = strs[0].substr(0, i);
                bool match = true;
                for (int j = 1; j < strs.size(); ++j) {
                    if (strs[j].length() < i || strs[j].substr(0, i) != sub) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    ret = sub;
                }
            }
            return ret;
        }
};

int main()
{
    return 0;
}


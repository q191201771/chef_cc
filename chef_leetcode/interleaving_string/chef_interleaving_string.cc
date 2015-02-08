/**
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
 * 
 * For example,
 *     Given:
 *     s1 = "aabcc",
 *     s2 = "dbbca",
 * 
 *     When s3 = "aadbbcbcac", return true.
 *     When s3 = "aadbbbaccc", return false.
 */

class Solution {
    public:
        bool isInterleave(string s1, string s2, string s3) {
            if (s1.length() + s2.length() != s3.length()) {
                return false;
            }

            vector<vector<bool> > arr(s1.length() + 1, vector<bool>(s2.length() + 1, false));
            arr[0][0] = true;
            for (int i = 1; i <= s1.length(); ++i) {
                if (s1[i - 1] == s3[i - 1]) {
                    arr[i][0] = true;
                } else {
                    break;
                }
            }
            for (int i = 1; i <= s2.length(); ++i) {
                if (s2[i - 1] == s3[i - 1]) {
                    arr[0][i] = true;
                } else {
                    break;
                }
            }

            for (int i = 1; i <= s1.length(); ++i) {
                for (int j = 1; j <= s2.length(); ++j) {
                    if (s1[i - 1] == s3[i + j - 1]) {
                        arr[i][j] = arr[i - 1][j];
                        if (arr[i][j]) {
                            continue;
                        }
                    }
                    if (s2[j - 1] == s3[i + j - 1]) {
                        arr[i][j] = arr[i][j - 1];
                    }
                }
            }
            return arr[s1.length()][s2.length()];
        }
};

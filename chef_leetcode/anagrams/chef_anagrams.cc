/**
 * Given an array of strings, return all groups of strings that are anagrams.
 * 
 * Note: All inputs will be in lower-case.
 */

class Solution {
    public:
        vector<string> anagrams(vector<string> &strs) {
            vector<string> ret;
            map<string, int> words;
            int i = 0;
            for (; i < strs.size(); ++i) {
                string word = strs[i];
                sort(word.begin(), word.end());
                if (words.find(word) == words.end()) {
                    words[word] = i; 
                } else {
                    if (words[word] >= 0) {
                        ret.push_back(strs[words[word]]);
                        words[word] = -1;
                    }
                    ret.push_back(strs[i]);
                }
            }
            return ret;
        }
};

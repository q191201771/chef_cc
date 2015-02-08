/**
 * Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 * 
 * For example,
 *     Given [100, 4, 200, 1, 3, 2],
 *     The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
 * 
 *     Your algorithm should run in O(n) complexity.
 */
class Solution {
    public:
        int longestConsecutive(vector<int> &num) {
            if (num.size() < 2) {
                return num.size();
            }

            set<int> s;
            for (int i = 0; i < num.size(); ++i) {
                s.insert(num[i]);
            }
            int ret = 1;
            int count = 1;
            set<int>::iterator iter = s.begin();
            int prev = *iter;
            ++iter;
            for (; iter != s.end(); ++iter) {
                if (*iter - prev == 1) {
                    ++count;
                } else {
                    count = 1;
                }
                if (count > ret) {
                    ret = count;
                }
                prev = *iter;
            }            
            return ret;
        }
};


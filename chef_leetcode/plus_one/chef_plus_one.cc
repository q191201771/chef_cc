/**
 * Given a non-negative number represented as an array of digits, plus one to the number.
 * 
 * The digits are stored such that the most significant digit is at the head of the list.
 */

class Solution {
    public:
        vector<int> plusOne(vector<int> &digits) {
            vector<int>::reverse_iterator iter = digits.rbegin();
            bool extend = false;
            for (; iter != digits.rend(); ++iter) {
                *iter += 1;
                if (*iter == 10) {
                    extend = true;
                    *iter = 0;
                } else {
                    extend = false;
                    break;
                }
            }
            if (extend) {
                digits.insert(digits.begin(), 1);
            }

            return digits;
        }
};



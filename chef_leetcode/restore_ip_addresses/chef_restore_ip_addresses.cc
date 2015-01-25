/**
 * Given a string containing only digits, restore it by returning all possible valid IP address combinations.
 * 
 * For example:
 * Given "25525511135",
 * 
 * return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

class Solution {
    public:
        bool valid(string str) {
            if (ip_.size() >= 4 || (str[0] == '0' && str.size() > 1)) {
                return false;
            }
            int num = atoi(str.c_str());
            if (num >= 0 && num <= 255) {
                return true;
            }
            return false;
        }

        void compute(int index) {
            if (index == s_.length()) {
                if (ip_.size() == 4) {
                    string ip;
                    for (int i = 0; i < 3; ++i) {
                        ip.append(ip_[i]);
                        ip.append(".");
                    }
                    ip.append(ip_[3]);
                    ret_.push_back(ip);
                }
                return;
            }
            for (int i = index; i < s_.length() && i - index <= 2; ++i) {
                string str = s_.substr(index, i - index + 1);
                if (valid(str)) {
                    ip_.push_back(str);
                    compute(i + 1);
                    ip_.pop_back();
                }
            }
        }

        vector<string> restoreIpAddresses(string s) {
            if (s.empty()) {
                return ret_;
            }
            s_ = s;
            compute(0);
            return ret_;
        }
    private:
        string s_;
        vector<string> ret_;
        vector<string> ip_;
};


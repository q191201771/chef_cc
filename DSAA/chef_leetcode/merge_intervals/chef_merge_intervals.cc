/**
 * Given a collection of intervals, merge all overlapping intervals.
 * 
 * For example,
 *     Given [1,3],[2,6],[8,10],[15,18],
 *     return [1,6],[8,10],[15,18].
 */

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

//Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

bool compare(const Interval &l, const Interval &r) {
    return (l.start == r.start) ? l.end < r.end : l.start < r.start;
}

class Solution {
    public:
        vector<Interval> merge(vector<Interval> &intervals) {
            vector<Interval> ret;
            if (intervals.size() <= 0) {
                return ret;
            }
            sort(intervals.begin(), intervals.end(), compare);
            for (int i = 0; i < intervals.size(); ++i) {
                vector<Interval>::reverse_iterator iter = ret.rbegin();
                if (iter == ret.rend()) {
                    ret.push_back(intervals[i]);
                } else {
                    if (iter->end >= intervals[i].start) {
                        if (iter->end < intervals[i].end) {
                            iter->end = intervals[i].end;
                        }
                    } else {
                        ret.push_back(intervals[i]);
                    }
                }
            }
        }
};


int main()
{
    vector<Interval> vec;
    vec.push_back(Interval(1, 4));
    vec.push_back(Interval(4, 5));
    Solution s;
    vector<Interval> ret = s.merge(vec);
    for (int i = 0; i < ret.size(); ++i) {
        printf("[%d,%d] ", ret[i].start, ret[i].end);
    }
    printf("\n");

    return 0;
}


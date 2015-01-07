/**
 * Merge k sorted linked lists and return it as one sorted list. Analyze and
 * describe its complexity.
 */

#include <stdio.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode *mergeKLists(vector<ListNode *> &lists) {
            if (lists.size() == 0) {
                return NULL;
            }
            while (lists.size() > 1) {
                ListNode *l1 = lists.back();
                lists.pop_back();
                ListNode *l2 = lists.back();
                lists.pop_back();
                ListNode *result = mergeTwoLists(l1, l2);
                lists.insert(lists.begin(), result);
            }
            return lists[0];
        }

        ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
            ListNode *ret = NULL;
            ListNode *p = NULL;
            for (; l1 || l2; ) {
                ListNode *node = new ListNode(0);
                if (l1 && l2) {
                    if (l1->val < l2->val) {
                        node->val = l1->val;
                        l1 = l1->next;
                    } else {
                        node->val = l2->val;
                        l2 = l2->next;
                    }
                } else if (l1) {
                    node->val = l1->val;
                    l1 = l1->next;
                } else if (l2) {
                    node->val = l2->val;
                    l2 = l2->next;
                }
                if (ret == NULL) {
                    ret = node;
                }
                if (p == NULL) {
                    p = node;
                } else {
                    p->next = node;
                    p = p->next;
                }
            }
            return ret;            
        }
};

int main()
{
    return 0;
}


/**
 * Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
 */

/**
 * Input:       {}, {0}
 * Expected:    {0}
 *
 * Input:       {2}, {1}
 * Expected:    {1,2}
 *
 * Input:       {1}, {2}
 * Expected:    {1,2}
 *
 * Input:       {}, {1,2,4}
 * Expected:    {1,2,4}
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


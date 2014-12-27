/**
 * Given a linked list, remove the nth node from the end of list and return its head.
 *
 * For example,
 *
 *      Given linked list: 1->2->3->4->5, and n = 2.
 *
 *      After removing the second node from the end, the linked list becomes 1->2->3->5.
 *      Note:
 *      Given n will always be valid.
 *      Try to do this in one pass.
 */

/**
 *   Definition for singly-linked list.
 *   struct ListNode {
 *      int val;
 *      ListNode *next;
 *      ListNode(int x) : val(x), next(NULL) {}
 *   };
 */

class Solution {
    public:
        ListNode *removeNthFromEnd(ListNode *head, int n) {

            int len = 0;
            ListNode *node = head;
            while(node) {
                ++len;
                node = node->next;
            }
            if (n == len) {
                head = head->next;
            } else {
                node = head;
                for (int i = 0; i < len - n - 1; ++i) {
                    node = node->next;
                }
                node->next = node->next ? node->next->next : node->next;
            }
            return head;
        }
};



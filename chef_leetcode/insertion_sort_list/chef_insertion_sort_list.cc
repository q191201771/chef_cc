/**
 * Sort a linked list using insertion sort.
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
    public:
        ListNode *insertionSortList(ListNode *head) {
            if (head == NULL || head->next == NULL) {
                return head;
            }
            ListNode head_prev(0);
            ListNode *node = head;
            while (node) {
                ListNode *next = node->next;
                ListNode *p = &head_prev;
                while (p->next) {
                    if (p->next->val > node->val) {
                        break;
                    }
                    p = p->next;
                }
                node->next = p->next;
                p->next = node;
                node = next;
            }

            return head_prev.next;
        }
};


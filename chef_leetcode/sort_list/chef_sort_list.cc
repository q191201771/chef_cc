/**
 * Sort a linked list in O(n log n) time using constant space complexity.
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
        ListNode *merge(ListNode *node1, ListNode *node2) {
            ListNode head_prev(0);
            ListNode *end = &head_prev;
            while (node1 || node2) {
                if (node1 && node2) {
                    if (node1->val < node2->val) {
                        end->next = node1;
                        end = node1;
                        node1 = node1->next;
                    } else {
                        end->next = node2;
                        end = node2;
                        node2 = node2->next;
                    }
                } else if (node1) {
                    end->next = node1;
                    end = node1;
                    node1 = node1->next;
                } else if (node2) {
                    end->next = node2;
                    end = node2;
                    node2 = node2->next;
                }
            }
            return head_prev.next;
        }

        ListNode *sortList(ListNode *head) {
            if (head == NULL || head->next == NULL) {
                return head;
            }
            ListNode *p1 = head;
            ListNode *p2 = head->next;
            while (p2 && p2->next) {
                p1 = p1->next;
                p2 = p2->next->next;
            }
            p2 = p1->next;
            p1->next = NULL;
            return merge(sortList(head), sortList(p2));
        }
};

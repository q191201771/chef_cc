/**
 * Given a linked list, swap every two adjacent nodes and return its head.
 * 
 * For example,
 *    Given 1->2->3->4, you should return the list as 2->1->4->3.
 *
 *    Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
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
        ListNode *swapPairs(ListNode *head) {
            if (head == NULL || head->next == NULL) {
                return head;
            }
            ListNode *ret = head->next;
            ListNode *p1 = head;
            ListNode *prev = NULL;
            
            for (p1 = head; p1 && p1->next; p1 = p1->next) {
                ListNode *p2 = p1->next;
                p1->next = p2->next;
                p2->next = p1;
                
                if (prev) {
                    prev->next = p2;
                }
                prev = p1;
            }
            return ret;
        }
};

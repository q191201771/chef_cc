/**
 * Given a sorted linked list, delete all duplicates such that each element
 * appear only once.
 *
 * For example,
 * Given 1->1->2, return 1->2.
 * Given 1->1->2->3->3, return 1->2->3.
 */

/**
 *  Definition for singly-linked list.
 *  struct ListNode {
 *      int val;
 *      ListNode *next;
 *      ListNode(int x) : val(x), next(NULL) {}
 *  };
 */        
class Solution {
    public:
        ListNode *deleteDuplicates(ListNode *head) {
            ListNode *node = head;
            while(node) {
                if (node->next == NULL) {
                    break;
                }
                if (node->val == node->next->val) {
                    node->next = node->next->next;
                } else {
                    node = node->next;
                }
            }
            return head;
        }
};


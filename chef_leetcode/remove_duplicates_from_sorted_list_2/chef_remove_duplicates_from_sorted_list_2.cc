/**
 * Given a sorted linked list, delete all nodes that have duplicate numbers,
 * leaving only distinct numbers from the original list.
 *
 * For example,
 * Given 1->2->3->3->4->4->5, return 1->2->5.
 * Given 1->1->1->2->3, return 2->3.
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
        ListNode *deleteDuplicates(ListNode *head) {
            if (head == NULL) {
                return NULL;
            }
            ListNode *ret = NULL;
            ListNode *end = NULL;
            bool erasing = false;
            int val;
            for (; head; head = head->next) {
                if (erasing && head->val == val) {
                    continue;
                }
                if (head->next == NULL || head->val != head->next->val) {
                    if (end) {
                        end->next = head;
                    }
                    end = head;
                    if (ret == NULL) {
                        ret = end;
                    }
                    erasing = false;
                } else {
                    val = head->val;
                    erasing = true;
                }
            }
            if (end) {
                end->next = NULL;
            }
            return ret;
        }
};


/**
 * Reverse a linked list from position m to n. Do it in-place and in one-pass.
 * 
 * For example:
 * Given 1->2->3->4->5->NULL, m = 2 and n = 4,
 * 
 *       return 1->4->3->2->5->NULL.
 * 
 *       Note:
 *       Given m, n satisfy the following condition:
 *       1 ≤ m ≤ n ≤ length of list.
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
        ListNode *reverseBetween(ListNode *head, int m, int n) {
            if (head == NULL || m <1 || n < m || n == m) {
                return head;
            }
            ListNode head_prev(0);
            head_prev.next = head;
            ListNode *bm = &head_prev;
            for (int i = 0; i < m - 1; ++i, bm = bm->next) {
                if (bm == NULL) {
                    return head;
                }
            }
            ListNode *iter = bm->next;
            ListNode *end = NULL;
            for (int j = 0; iter && j <= n - m; ++j) {
                if (iter == bm->next) {
                    end = iter;
                    iter = iter->next;
                    continue;
                }
                ListNode *next = iter->next;
                iter->next = bm->next;
                bm->next = iter;
                iter = next;
            }
            if (end) {
                end->next = iter;
            }
            return head_prev.next;
        }
};

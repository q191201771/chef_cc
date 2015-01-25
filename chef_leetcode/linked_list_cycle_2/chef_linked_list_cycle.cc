/**
 * Given a linked list, return the node where the cycle begins. If there is no
 * cycle, return null.
 *
 * Follow up:
 * Can you solve it without using extra space?
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

///{-21,10,17,8,4,26,5,35,33,-7,-16,27,-12,6,29,-12,5,9,20,14,14,2,13,-24,21,23,-21,5}

class Solution {
    private:
        ListNode *p1;
        ListNode *p2;
    public:
        ListNode *detectCycle(ListNode *head) {
            if (!hasCyclde(head)) {
                return NULL;
            }
            p1 = head;
            while (p1 != p2) {
                p1 = p1->next;
                p2 = p2->next;
            } 
            return p1;
        }

        bool hasCycle(ListNode *head) {
            if (head == NULL || head->next == NULL) {
                return false;
            }
            p1 = head->next;
            p2 = head->next->next;

            while (p1 && p2) {
                if (p1 == p2) {
                    return true;
                }
                p1 = p1->next;
                if (p2->next == NULL) {
                    return false;
                }
                p2 = p2->next->next;
            }

            return false;
        }
};

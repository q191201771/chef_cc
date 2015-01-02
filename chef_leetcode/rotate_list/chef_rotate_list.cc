/**
 * Given a list, rotate the list to the right by k places, where k is non-negative.
 * 
 * For example:
 * Given 1->2->3->4->5->NULL and k = 2,
 *       return 4->5->1->2->3->NULL.
 */


#include <stdio.h>

//  Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode *rotateRight(ListNode *head, int k) {
            int len = 0;
            ListNode *node = head;
            ListNode *tail;
            while(node) {
                ++len;
                tail = node;
                node = node->next;
            }
            if (k <= 0 || len <= 0) {
                return head;
            }
            
            /**
             * {1, 2}, 3
             * {2, 1}
             */
            if (k >= len) {
                k %= len;
            }

            node = head;
            for (int i = 0; i < len - k - 1; ++i) {
                node = node->next;
            }
            tail->next = head;
            head = node->next;
            node->next = NULL;
            return head;
        }
};

int main()
{
    ListNode *node = new ListNode(1);
    node->next = new ListNode(2);
    Solution s;
    ListNode *node2 = s.rotateRight(node, 1);
    while(node2) {
        printf("%d ", node2->val);
        node2 = node2->next;
    }
    printf("\n");

    return 0;
}

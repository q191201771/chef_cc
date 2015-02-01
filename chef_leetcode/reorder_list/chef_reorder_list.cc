/**
 * Given a singly linked list L: L0→L1→…→Ln-1→Ln,
 *       reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
 * 
 *       You must do this in-place without altering the nodes' values.
 * 
 *       For example,
 *       Given {1,2,3,4}, reorder it to {1,4,2,3}.
 */

#include <stdio.h>

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void print(ListNode *node) {
    printf("-----\n");
    for (; node; node = node->next) {
        printf("%d", node->val);
    }
    printf("\n-----\n");
}

class Solution {
    public:
        void reorderList(ListNode *head) {
            if (head == NULL) {
                return;
            }
            int len = 0;
            ListNode *p1= head;
            for (; p1; p1 = p1->next) {
                ++len;
            }
            if (len < 3) {
                return;
            }
            /// get mid
            p1 = head;
            for (int i = 0; i < (len + 1) / 2 - 1; ++i) {
                p1 = p1->next;
            }
            ListNode *p2 = p1->next;
            p1->next = NULL;
            /// reverse part 2
            ListNode prev(0);
            for (; p2; ) {
                ListNode *next = p2->next;
                p2->next = prev.next;
                prev.next = p2;
                p2 = next;
            }
            //print(prev.next);
            /// merge
            p1 = head;
            p2 = prev.next;
            for (; p1 || p2; ) {
                ListNode *next1 = NULL;
                ListNode *next2 = NULL;
                if (p1) {
                    next1 = p1->next;
                    p1->next = p2;
                }
                if (p2) {
                    next2 = p2->next;
                    p2->next = next1;
                }
                p1 = next1;
                p2 = next2;
            }
            return;
        }
};

int main()
{
    ListNode node1(1), node2(2), node3(3), node4(4);
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    Solution s;
    s.reorderList(&node1);
    print(&node1);

    return 0;
}


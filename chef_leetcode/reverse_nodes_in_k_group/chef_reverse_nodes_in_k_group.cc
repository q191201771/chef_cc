/**
 * Given a linked list, reverse the nodes of a linked list k at a time and
 * return its modified list.
 *
 * If the number of nodes is not a multiple of k then left-out nodes in the end
 * should remain as it is.
 *
 * You may not alter the values in the nodes, only nodes itself may be changed.
 *
 * Only constant memory is allowed.
 *
 * For example,
 * Given this linked list: 1->2->3->4->5
 *
 * For k = 2, you should return: 2->1->4->3->5
 *
 * For k = 3, you should return: 3->2->1->4->5
 */


#include <stdio.h>

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void print(ListNode *head) {
    printf("-----\n");
    for (; head; head = head->next) {
        printf("%d", head->val);
    }
    printf("\n-----\n");
}

class Solution {
    public:
        ListNode *reverseKGroup(ListNode *head, int k) {
            if (head == NULL || k < 2) {
                return head;
            }
            ListNode head_prev(0);
            head_prev.next = head;
            ListNode *left_tail = &head_prev;
            for (; ; ) {
                ListNode *p = left_tail->next;
                for (int i = 0; i < k; ++i) {
                    if (p == NULL) {
                        return head_prev.next;
                    }
                    p = p->next;
                }
                ListNode *right_head = p;
                ListNode *new_left_tail = left_tail->next;
                p = left_tail->next;
                left_tail->next = right_head;
                for (; p != right_head;) {
                    ListNode *next = p->next;
                    p->next = left_tail->next;
                    left_tail->next = p; 
                    p = next;
                }
                left_tail = new_left_tail;
            }
            return NULL;
        }
};

int main()
{
    Solution s;
    ListNode n1(1);
    ListNode n2(2);
    ListNode n3(3);
    ListNode n4(4);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;

    ListNode *ret = s.reverseKGroup(&n1, 2);
    print(ret);

    return 0;
}


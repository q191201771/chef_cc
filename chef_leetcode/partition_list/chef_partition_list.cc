/**
 * Given a linked list and a value x, partition it such that all nodes less than
 * x come before nodes greater than or equal to x.
 *
 * You should preserve the original relative order of the nodes in each of the
 * two partitions.
 *
 * For example,
 * Given 1->4->3->2->5->2 and x = 3,
 * return 1->2->2->4->3->5.
 */

#include <stdio.h>

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode *partition(ListNode *head, int x) {
            ListNode *left_begin = NULL;
            ListNode *left_end = NULL;
            ListNode *right_begin = NULL;
            ListNode *right_end = NULL;

            for (; head; head = head->next) {
                if (head->val < x) {
                    if (!left_begin) {
                        left_begin = head;
                    }
                    if (left_end) {
                        left_end->next = head;
                    }
                    left_end = head;
                } else {
                    if (!right_begin) {
                        right_begin = head;
                    }
                    if (right_end) {
                        right_end->next = head;
                    }
                    right_end = head;
                }
            }
            if (right_end) {
                right_end->next = NULL;
            }
            if (left_end && right_begin) {
                left_end->next = right_begin;
            }
            if (left_begin) {
                return left_begin;
            } else if (right_begin) {
                return right_begin;
            }
            return NULL;
        }
};

int main()
{
    ListNode node1(2);
    ListNode node2(1);
    node1.next = &node2;
    Solution s;
    ListNode *ret = s.partition(&node1, 2);
    for (; ret; ret = ret->next) {
        printf("%d", ret->val);
    }
    printf("\n");
    return 0;
}

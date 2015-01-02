/**
 * You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 * 
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 *     Output: 7 -> 0 -> 8
 */

/**
 * Definition for singly-linked list.
 */

#include <stdio.h>
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
            ListNode *head = NULL;
            ListNode *node = NULL;
            ListNode *pos = NULL;
            bool extend = false;
            while(l1 || l2 || extend) {
                node = new ListNode(0);
                if (head == NULL) {
                    head = node;
                }
                if (l1) {
                    node->val += l1->val;
                    l1 = l1->next;
                }
                if (l2) {
                    node->val += l2->val;
                    l2 = l2->next;
                }
                if (extend) {
                    node->val += 1;
                }
                if (node->val >= 10) {
                    node->val -= 10;
                    extend = true;
                } else {
                    extend = false;
                }
                if (pos) {
                    pos->next = node;
                    pos = pos->next;
                } else {
                    pos = node;
                }
            }
            return head;
        }
};

int main()
{
    Solution s;
    ListNode *l1 = new ListNode(1);
    ListNode *l2 = new ListNode(9);
    ListNode *node = new ListNode(9);
    l2->next = node;
    ListNode *ret = s.addTwoNumbers(l1, l2);
//    printf("~~~~~\n");
//    for (; ret; ret = ret->next) {
//        printf("%d ", ret->val);
//    }
//    printf("\n");
    return 0;
}


/**
 * Given a singly linked list where elements are sorted in ascending order,
 * convert it to a height balanced BST.
 */


#include <stdio.h>

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};



//Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
    public:
        TreeNode *sort(ListNode *&head, int left, int right) {
            if (head == NULL || left > right) {
                return NULL;
            }
            int mid = (right + left) / 2;
            TreeNode *left_node = sort(head, left, mid - 1);
            
            TreeNode *node = new TreeNode(head->val);
            node->left = left_node;
            head = head->next;
            node->right = sort(head, mid + 1, right);

            return node;
        }

        TreeNode *sortedListToBST(ListNode *head) {
            if (head == NULL) {
                return NULL;
            }

            int size = 0;
            for (ListNode *p = head; p; p = p->next) {
                ++size;
            }
            return sort(head, 0, size - 1);
        }
};

void print_tree(TreeNode *node) {
    if (node == NULL) {
        printf("NULL\n");
        return;
    }
    printf("%d\n", node->val);
    print_tree(node->left);
    print_tree(node->right);
}

int main()
{
    ListNode node1(-10);
    ListNode node2(-3);
    ListNode node3(0);
    ListNode node4(5);
    ListNode node5(9);
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;

    Solution s;
    TreeNode *node = s.sortedListToBST(&node1);

    printf("-----\n");
    print_tree(node);

    return 0;
}


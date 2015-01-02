/**
 * Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
 * 
 * For example, this binary tree is symmetric:
 * 
 *     1
 *    / \
 *   2   2
 *  / \ / \
 * 3  4 4  3
 * But the following is not:
 *     1
 *    / \
 *   2   2
 *    \   \
 *    3    3
 */

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
    public:
        bool isSymmetric(TreeNode *root) {
            if (root == NULL) {
                return true;
            }
            return isSymmetric(root->left, root->right);
        }
        bool isSymmetric(TreeNode *p, TreeNode *q) {
            if (p == q) {
                return true;
            }
            if (!(p && q && p->val == q->val)) {
                return false;
            }
            return isSymmetric(p->left, q->right) && isSymmetric(p->right, q->left);
        }
};


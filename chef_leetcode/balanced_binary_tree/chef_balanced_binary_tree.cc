/**
 * Given a binary tree, determine if it is height-balanced.
 *
 * For this problem, a height-balanced binary tree is defined as a binary tree
 * in which the depth of the two subtrees of every node never differ by more
 * than 1.
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
        bool isBalanced(TreeNode *root) {
            if (root == NULL) {
                return true;
            }

            int left = compute_depth(root->left); 
            int right = compute_depth(root->right);
            if (left - right > 1 || left - right < -1) {
                return false;
            }
            return isBalanced(root->left) && isBalanced(root->right);
        }
        int compute_depth(TreeNode *root) {
            if (root == NULL) {
                return 0;
            }
            int left = 1;
            int right = 1;
            left += compute_depth(root->left);
            right += compute_depth(root->right);
            return left > right ? left : right;
        }
};

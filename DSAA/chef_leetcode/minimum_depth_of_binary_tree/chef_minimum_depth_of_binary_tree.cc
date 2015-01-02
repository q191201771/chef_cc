/**
 * Given a binary tree, find its minimum depth.
 * 
 * The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
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
        int minDepth(TreeNode *root) {
            if (root == NULL) {
                return 0;
            }
            if (root->left == NULL && root->right == NULL) {
                return 1;
            }

            int left_len = INT_MAX;
            if (root->left) {
                left_len = minDepth(root->left) + 1;
            }
            int right_len = INT_MAX;
            if (root->right) {
                right_len = minDepth(root->right) + 1;
            }
            return left_len < right_len ? left_len : right_len;
        }
};

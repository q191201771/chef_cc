/**
 * Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
 * 
 * An example is the root-to-leaf path 1->2->3 which represents the number 123.
 * 
 * Find the total sum of all root-to-leaf numbers.
 * 
 * For example,
 * 
 *         1
 *        / \
 *       2   3
 *       The root-to-leaf path 1->2 represents the number 12.
 *       The root-to-leaf path 1->3 represents the number 13.
 *
 *       Return the sum = 12 + 13 = 25.
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
        int sumNumbers(TreeNode *root) {
            if (root == NULL) {
                return 0;
            }
            int ret = 0;
            vector<TreeNode *> nodes;
            nodes.push_back(root);
            int i = 0;
            while(i < nodes.size()) {
                root = nodes[i];
                if (root->left) {
                    root->left->val += root->val * 10;
                    nodes.push_back(root->left);
                }
                if (root->right) {
                    root->right->val += root->val * 10;
                    nodes.push_back(root->right);
                }
                if (root->left == NULL && root->right == NULL) {
                    ret += root->val;
                }
                ++i;
            }
            return ret;
        }
};

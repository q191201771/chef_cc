/**
 * Given a binary tree, return the inorder traversal of its nodes' values.
 * 
 * For example:
 * Given binary tree {1,#,2,3},
 *          1
 *           \
 *            2
 *           /
 *          3
 * return [1,3,2].
 *
 * Note: Recursive solution is trivial, could you do it iteratively?
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
        vector<int> inorderTraversal(TreeNode *root) {
            stack<TreeNode *> nodes;
            vector<int> ret;

            while(root || !nodes.empty()) {
                if (root) {
                    nodes.push(root);
                    root = root->left;
                } else {
                    if (!nodes.empty()) {
                        root = nodes.top();
                        nodes.pop();
                        ret.push_back(root->val);
                        root = root->right;
                    }
                }
            }
            return ret;
        }
};

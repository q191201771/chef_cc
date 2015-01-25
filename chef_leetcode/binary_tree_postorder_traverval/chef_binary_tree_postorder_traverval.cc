/**
 * Given a binary tree, return the postorder traversal of its nodes' values.
 * 
 * For example:
 * Given binary tree {1,#,2,3},
 *       1
 *        \
 *         2
 *        /
 *       3
 * return [3,2,1].
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
        vector<int> postorderTraversal(TreeNode *root) {
            compute(root);
            return ret_;    
        }
        void compute(TreeNode *root) {
            if (root == NULL) {
                return;
            }
            compute(root->left);
            compute(root->right);
            ret_.push_back(root->val);
        }

    private:
        vector<int> ret_;
};

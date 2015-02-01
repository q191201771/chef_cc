/**
 * Given a binary tree, determine if it is a valid binary search tree (BST).
 * 
 * Assume a BST is defined as follows:
 * 
 * The left subtree of a node contains only nodes with keys less than the node's key.
 * The right subtree of a node contains only nodes with keys greater than the node's key.
 * Both the left and right subtrees must also be binary search trees.
 */

/**
 * Definition for binary tree
 * struct TreeNode {
 *    int val;
 *    TreeNode *left;
 *    TreeNode *right;
 *    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    public:
        void fun(TreeNode *node, vector<int> &nodes) {
            if (node == NULL) {
                return;
            }
            fun(node->left, nodes);
            nodes.push_back(node->val);
            fun(node->right, nodes);
        }

        bool isValidBST(TreeNode *root) {
            if (root == NULL) {
                return true;
            }
            vector<int> nodes;
            fun(root, nodes);
            for (int i = 0; i < nodes.size() - 1; ++i) {
                if (nodes[i] >= nodes[i + 1]) {
                    return false;
                }
            }
            return true;
        }
};

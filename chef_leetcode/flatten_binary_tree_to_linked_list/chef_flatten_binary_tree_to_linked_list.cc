/**
 * Given a binary tree, flatten it to a linked list in-place.
 * 
 * For example,
 *     Given
 * 
 *              1
 *             / \
 *            2   5
 *           / \   \
 *          3   4   6
 *     The flattened tree should look like:
 *         1
 *          \
 *           2
 *            \
 *             3
 *              \
 *               4
 *                \
 *                 5
 *                  \
 *                   6
 *
 * Hints:
 * If you notice carefully in the flattened tree, each node's right child points
 * to the next node of a pre-order traversal.
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
        void flatten(TreeNode *root) {
            if (root == NULL) {
                return;
            }
            vector<TreeNode *> s1, s2;
            s1.push_back(root);
            while(!s1.empty()) {
                TreeNode *node = s1.back();
                s2.push_back(node);
                s1.pop_back();

                if (node->right) {
                    s1.push_back(node->right);
                }
                if (node->left) {
                    s1.push_back(node->left);
                }
            }
            int i = 0;
            for (; i < s2.size() - 1; ++i) {
                s2[i]->left = NULL;
                s2[i]->right = s2[i + 1];
            }
            s2[i]->left = NULL;
            s2[i]->right = NULL;
        }
};

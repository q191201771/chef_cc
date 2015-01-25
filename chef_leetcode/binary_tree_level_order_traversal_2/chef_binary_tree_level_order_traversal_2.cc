/**
 * Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).
 * 
 * For example:
 * Given binary tree {3,9,20,#,#,15,7},
 *           3
 *          / \
 *         9  20
 *           /  \
 *          15   7
 * return its bottom-up level order traversal as:
 * [
 *   [15,7],
 *   [9,20],
 *   [3]
 * ]
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
        vector<vector<int> > levelOrderBottom(TreeNode *root) {
            vector<vector<int> > ret;
            vector<vector<TreeNode *> > nodes;
            if (root == NULL) {
                return ret;
            }
            nodes.push_back(vector<TreeNode *>(1, root));
            for (int i = 0; i < nodes.size(); ++i) {
                vector<TreeNode *> vec;
                for (int j = 0; j < nodes[i].size(); ++j) {
                    if (nodes[i][j]->left) {
                        vec.push_back(nodes[i][j]->left);
                    }
                    if (nodes[i][j]->right) {
                        vec.push_back(nodes[i][j]->right);
                    }
                }
                if (!vec.empty()) {
                    nodes.push_back(vec);
                }
            }

            for (int i = nodes.size() - 1; i >= 0; --i) {
                vector<int> sub;
                for (int j = 0; j < nodes[i].size(); ++j) {
                    sub.push_back(nodes[i][j]->val);
                }
                ret.push_back(sub);
            }
            return ret;
        }
};


/**
 * Follow up for problem "Populating Next Right Pointers in Each Node".
 * 
 * What if the given tree could be any binary tree? Would your previous solution still work?
 * 
 * Note:
 * 
 * You may only use constant extra space.
 * For example,
 *     Given the following binary tree,
 *               1
 *             /  \
 *            2    3
 *           / \    \
 *          4   5    7
 *      After calling your function, the tree should look like:
 *          1 -> NULL
 *        /  \
 *       2 -> 3 -> NULL
 *      / \    \
 *     4-> 5 -> 7 -> NULL
 */

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *   int val;
 *   TreeLinkNode *left, *right, *next;
 *   TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
    public:
        void connect(TreeLinkNode *root) {
            if (root == NULL) {
                return;
            }

            vector<vector<TreeLinkNode *> > nodes;
            nodes.push_back(vector<TreeLinkNode *>(1, root));

            for (int i = 0; i < nodes.size(); ++i) {
                vector<TreeLinkNode *> vec;
                for (int j = 0; j < nodes[i].size(); ++j) {
                    if (j != nodes[i].size() - 1) {
                        nodes[i][j]->next = nodes[i][j + 1];
                    }
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
        }
};

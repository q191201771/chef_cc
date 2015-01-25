/**
 * Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
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
        TreeNode *sortedArrayToBST(vector<int> &num) {
            int size = num.size();
            if (size == 0) {
                return NULL;
            }
            if (size == 1) {
                return new TreeNode(num[0]);
            }
            int mid = size / 2;
            TreeNode *node = new TreeNode(num[mid]);

            vector<int>::iterator begin = num.begin();
            vector<int>::iterator left = begin + mid;
            vector<int>::iterator right = left + 1;
            vector<int> left_vec(begin, left);
            node->left = sortedArrayToBST(left_vec);
            if (right != num.end()) {
                vector<int> right_vec(right, num.end());
                node->right = sortedArrayToBST(right_vec);
            } else {
                node->right = NULL;
            }
            return node;
        }
};

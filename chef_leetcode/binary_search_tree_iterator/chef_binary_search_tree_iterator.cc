/**
 * Implement an iterator over a binary search tree (BST). Your iterator will be
 * initialized with the root node of a BST.
 *
 * Calling next() will return the next smallest number in the BST.
 *
 * Note: next() and hasNext() should run in average O(1) time and uses O(h)
 * memory, where h is the height of the tree.
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
class BSTIterator {
    private:
        int pos_;
        vector<int> vals_;
    public:
        BSTIterator(TreeNode *root) {
            pos_ = 0;
            vector<TreeNode *> nodes;
            while (!nodes.empty() || root != NULL) {
                if (root) {
                    nodes.push_back(root);
                    root = root->left;
                } else {
                    root = nodes.back();
                    nodes.pop_back();
                    vals_.push_back(root->val);
                    root = root->right;
                }
            }
        }

        /** @return whether we have a next smallest number */
        bool hasNext() {
            return pos_ < vals_.size();
        }

        /** @return the next smallest number */
        int next() {
            return vals_[pos_++];
        }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

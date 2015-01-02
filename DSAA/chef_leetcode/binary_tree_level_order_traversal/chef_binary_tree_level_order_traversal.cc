/**
 * Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
 * 
 * For example:
 * Given binary tree {3,9,20,#,#,15,7},
 *           3
 *          / \
 *         9  20
 *           /  \
 *          15   7
 * return its level order traversal as:
 * [
 *   [3],
 *   [9,20],
 *   [15,7]
 * ]
 */

/**
 *   [1,2,#,3,#,4,#,5]
 *         1
 *        /
 *       2  
 *      / 
 *     3
 *    /  
 *   4
 *  /
 * 5
 *
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
        vector<vector<int> > levelOrder(TreeNode *root) {                       
            vector<vector<int> > ret;                                           
            if (root == NULL) {                                                 
                return ret;                                                     
            }                                                                   
            queue<TreeNode *> q;                                                
            vector<TreeNode *> nodes;                                           
            q.push(root);                                                       
            while(!q.empty()) {                                                 
                TreeNode *node = q.front();                                     
                q.pop();                                                        
                nodes.push_back(node);                                          
                if (node == NULL) {                                             
                    continue;                                                   
                }                                                               
                q.push(node->left);                                             
                q.push(node->right);                                            
            }                                                                   

            int size = 1;                                                       
            int count = 0;                                                      
            vector<int> vec;                                                    
            for (int i = 0; i < nodes.size(); ++i) {                            
                if (nodes[i] != NULL) {                                         
                    vec.push_back(nodes[i]->val);                               
                }                                                               
                if (++count == size) {                                          
                    if (!vec.empty()) {                                       
                        ret.push_back(vec);                                     
                    }                                                         

                    size = vec.size() * 2;                                      
                    vec.clear();                                                
                    count = 0;                                                  
                }                                                               
            }                                                                   
            if (!vec.empty()) {                                               
                ret.push_back(vec);                                           
            }                                                                 
            return ret;                                                         
        }                                                                       
};

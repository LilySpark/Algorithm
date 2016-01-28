#include <iostream>

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    bool isIdentity(TreeNode* left, TreeNode* right)
    {
        if(left==NULL && right==NULL)
            return true;
        if(right == NULL or left == NULL)
            return false;
        return left->val == right->val && isIdentity(left->left, right->right) && isIdentity(left->right, right->left);
    }
    bool isSymmetric(TreeNode* root) {
        if(root==NULL)
            return true;
        return isIdentity(root->left, root->right);
    }
};





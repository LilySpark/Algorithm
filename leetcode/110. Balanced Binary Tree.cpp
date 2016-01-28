#include<iostream>


 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int treeHeight(TreeNode* root)
    {
        int height;
        if(root==NULL)
            height =  0;
        else{
            int lh = treeHeight(root->left) + 1;
            int rh = treeHeight(root->right) + 1;
            height = lh>rh?lh:rh;
        }

        return height;
    }
    bool isBalanced(TreeNode* root) {
        if(root == NULL)
            return true;
        int lh = treeHeight(root->left);
        int rh = treeHeight(root->right);
        if(lh - rh > 1 or lh - rh < -1)
            return false;
        return isBalanced(root->left) && isBalanced(root->right);

    }
};

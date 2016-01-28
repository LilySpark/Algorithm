#include <iostream>

using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
    int mindepth = 0;
public:
    void dfs(TreeNode* root,int dep){
        if(root->left)
            dfs(root->left,dep+1);
        if(root->right)
            dfs(root->right,dep+1);
        if(root->left==NULL && root->right==NULL)
        {
            if(mindepth==0)
                mindepth = dep;
            if(mindepth > dep)
                mindepth = dep;
        }
    }
    int minDepth(TreeNode* root) {
        if(root)
            dfs(root,1);
        return mindepth;
    }
};

class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        if (root->left &&  root->right)
            return min(minDepth(root->left), minDepth(root->right)) + 1;
        return max(minDepth(root->left), minDepth(root->right)) + 1;
    }
};





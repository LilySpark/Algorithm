#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:

    bool dfs(TreeNode* root, int& pathsum, int sum)
    {
        pathsum += root->val;
        int flag = false;
        if(root->left){
           flag = dfs(root->left,pathsum,sum);
           if(flag)
                return true;
        }
        if(root->right){
            flag = dfs(root->right,pathsum,sum);
            if(flag)
                return true;
        }
        if(root->left == NULL && root->right==NULL)
            if(pathsum == sum)
                return true;

        pathsum -= root->val;
        return false;
    }
    bool hasPathSum(TreeNode* root, int sum) {
        int pathSum = 0;
        if(root==NULL)
            return false;
        return dfs(root,pathSum,sum);
    }
};

#include<iostream>
#include<algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    int maxdepth=0;
public:
    void dfs(TreeNode* root,int dep){
        if(root->left)
            dfs(root->left,dep+1);
        if(root->right)
            dfs(root->right,dep+1);
        if(!root->left && !root->right)
            maxdepth = max(maxdepth, dep+1);

    }
    int maxDepth(TreeNode* root) {
        int dep=0;
        if(!root)
            return 0;

        dfs(root,dep);

        return maxdepth;

    }
};

int main()
{
    return 0;
}

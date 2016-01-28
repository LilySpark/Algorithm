#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;


struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        queue<TreeNode*> q;
        queue<int> qlevel;
        stack<vector<int>> res;
        vector<vector<int>> result;
        if(root==NULL)
            return result;

        q.push(root);
        qlevel.push(0);
        int level = 0;
        vector<int> levelNodes;
        while(!q.empty()){
            TreeNode* top = q.front();
            int curLeval = qlevel.front();
            q.pop();
            qlevel.pop();
            if(top->left ){
                q.push(top->left);
                qlevel.push(curLeval+1);
            }
            if(top->right){
                q.push(top->right);
                qlevel.push(curLeval+1);
            }
            if(curLeval!=level){
                res.push(levelNodes);
                levelNodes.clear();
                level = curLeval;
            }
            levelNodes.push_back(top->val);
        }
        res.push(levelNodes);
        while(!res.empty())
        {
            result.push_back(res.top());
            res.pop();
        }

        return result;
    }
};

#include<iostream>
#include<vector>
#include<queue>

using namespace std;


struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        queue<int> qlevel;
        vector<vector<int>> res;
        if(root==NULL)
            return res;

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
                res.push_back(levelNodes);
                levelNodes.clear();
                level = curLeval;
            }
            levelNodes.push_back(top->val);
        }
        res.push_back(levelNodes);

        return res;
    }
};

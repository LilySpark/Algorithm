#include <iostream>
#include <vector>
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        if(root){
            non_rec_preorder(root, result);
           // rec_preorder(root, result);
        }
        return result;
    }

    void non_rec_preorder(TreeNode* root, vector<int>& result) {
        stack<TreeNode*> nodes;
        nodes.push(root);
        while(!nodes.empty())
        {
            TreeNode* p = nodes.top();
            result.push_back(p->val);
            nodes.pop();
            if(p->right)
                nodes.push(p->right);
            if(p->left)
                nodes.push(p->left);
        }
    }

    void rec_preorder(TreeNode* p, vector<int>& result)
    {
        result.push_back(p->val);
        if(p->left)
            recursivePreorder(p->left, result);
        if(p->right)
            recursivePreorder(p->right, result);
    }
};

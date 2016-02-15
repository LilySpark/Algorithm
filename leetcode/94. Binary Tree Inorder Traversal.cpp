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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(root){
           non_rec_inorder(root, result);
           //rec_inorder(root, result);
        }
        return result;
    }

    void non_rec_inorder(TreeNode* root, vector<int>& result) {
        stack<TreeNode*> nodes;
        TreeNode* curNode = root;
        while(!nodes.empty() || curNode)
        {
            while(curNode){
                nodes.push(curNode);
                curNode = curNode -> left;
            }
            curNode = nodes.top();
            result.push_back(curNode -> val);
            nodes.pop();
            curNode = curNode -> right;
        }
    }

    void rec_inorder(TreeNode* p, vector<int>& result)
    {
        if(p->left)
            rec_inorder(p->left, result);
        result.push_back(p->val);
        if(p->right)
            rec_inorder(p->right, result);
    }
};

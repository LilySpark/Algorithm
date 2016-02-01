<<<<<<< HEAD
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {

private:
    string toString(int val)
    {
        char str[100];
        string s;
        sprintf(str, "%d", val);
        s = str;
        return s;
    }
public:
    void dfs(TreeNode* root, vector<string>& path, string pathstr)
    {
        if(root->left)
            dfs(root->left, path, pathstr+"->"+toString(root->left->val));
        if(root->right)
            dfs(root->right, path, pathstr+"->"+toString(root->right->val));
        if(!root->left && !root->right)
            path.push_back(pathstr);
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> path;
        if(root)
            dfs(root, path, toString(root->val));
        return path;
    }
};

int main()
{
    return 0;
}


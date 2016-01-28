struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {

        if(p==NULL && q==NULL)
            return true;
        else if(p==NULL or q == NULL)
            return false;
        else{
            if(p->val!=q->val)
                return false;

            bool left = isSameTree(p->left, q->left);
            bool right = isSameTree(p->right, q->right);
            if(left && right)
                return true;
            else
                return false;
        }
    }
};

//解题思路：
//根据BST的性质，左子树节点的值＜根节点的值，右子树节点的值＞根节点的值
//记当前节点为node，从根节点root出发
//若p与q分别位于node的两侧，或其中之一的值与node相同，则node为LCA
//若p的值小于node的值，则LCA位于node的左子树
//否则，LCA位于node的右子树
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if(root){
			if( (p->val - root->val)*(q->val - root->val)<=0 )  return root;
			else if (p->val < root->val)
				return lowestCommonAncestor(root->left, p, q);
			else
				return lowestCommonAncestor(root->right, p, q);
		}
	}
};

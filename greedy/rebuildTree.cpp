#include <iostream>
#include <queue>
using namespace std;

//树节点类
class TNode
{
public:
    TNode *left, *right;
    char value;
    TNode()
    {
        left = right = NULL;
    }

    TNode(char v)
    {
        left = right = NULL;
        value = v;
    }

};

//根据二叉树的先序遍历和中序遍历重建二叉树
//PreOrder为二叉树的先序遍历 InOrder为二叉树中序遍历
TNode* RebuildTree(string PreOrder, string InOrder)
{
    //先序遍历中第一个元素为根
    TNode* root = new TNode(PreOrder[0]);

    //只剩一个节点的情况 直接返回节点
    if (PreOrder.length() <= 1)
        return root;

    //在中序遍历中找到根 根左边的部分为左子树 右边的部分为右子树
    string LeftChild = InOrder.substr(0, InOrder.find(PreOrder[0]));
    string RightChild = InOrder.substr(InOrder.find(PreOrder[0])+1);

    //递归建立左右子树
    if (LeftChild.length())
        root->left = RebuildTree(PreOrder.substr(1, LeftChild.length()), LeftChild);
    if (RightChild.length())
        root->right = RebuildTree(PreOrder.substr(1 + LeftChild.length()), RightChild);

    return root;
}


//二叉树先序遍历
void PrevOrder(TNode *root)
{
    if(root == NULL)
        return;
    //访问根
    cout << root->value;
    //访问左子树
    if(root->left)
        PrevOrder(root->left);
    //访问右子树
    if(root->right)
        PrevOrder(root->right);
}

//二叉树中序遍历
void InOrder(TNode *root)
{
    if(root == NULL)
        return;
    //访问左子树
    if(root->left)
        InOrder(root->left);
    //访问根
    cout << root->value;
    //访问右子树
    if(root->right)
        InOrder(root->right);
}

//二叉树后序遍历
void PostOrder(TNode *root)
{
    if(root == NULL)
        return;
    //访问左子树
    if(root->left)
        PostOrder(root->left);
    //访问右子树
    if(root->right)
        PostOrder(root->right);
    //访问根
    cout << root->value;
}

//二叉树层次遍历
void BFS(TNode *root)
{
    //用队列储存
    queue<TNode*> nodes;
    //根节点入队
    nodes.push(root);

    while (!nodes.empty())
    {
        TNode* top = nodes.front();
        //输出队头元素
        cout << top->value;
        //左子树入队
        if (top->left)
            nodes.push(top->left);
        //右子树入队
        if (top->right)
            nodes.push(top->right);
        //弹出队头
        nodes.pop();
    }
    cout << endl;
}

int main()
{
    string Prev, In;
    int t;
    cin >> t;
    while (t--)
    {
        cin >> Prev >> In;
        TNode *root = RebuildTree(Prev, In);
//        cout << "PreOrder: ";
//        PrevOrder(root);
//        cout << endl << "InOrder: ";
//        InOrder(root);
//        cout << endl << "PostOrder: ";
//        PostOrder(root);
//        cout << endl << "BFS: ";
        BFS(root);
//        cout << endl;
    }
    return 0;
}

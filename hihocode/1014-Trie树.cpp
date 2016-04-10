#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct TreeNode{

    int count;
    char a;
    bool isEnd;
    vector<struct TreeNode*> nextNode;
    TreeNode():count(0),a(' '),isEnd(false){};
    TreeNode(int c, char b, bool end):count(c),a(b),isEnd(false){};
    ~TreeNode()
    {
        for(int i = 0; i < nextNode.size(); i++)
            delete nextNode[i];
    }
};

class Trie
{
    private:
        TreeNode* head;
    public:
        Trie();
        ~Trie();
        void addWord(string word);
        int searchWord(string word);
};

Trie::Trie()
{
    head = new TreeNode(0,' ', false);
}
Trie::~Trie()
{
    delete head;
}

void Trie::addWord(string word)
{
    head->count += 1;
    vector<struct TreeNode*> next = head->nextNode;
    TreeNode* p = head;

    int i,j;

    for(i = 0; i < word.size(); i++)
    {
         int len = next.size();
         for(j = 0; j < len; j++)
         {
             if(next[j]->a == word[i])
             {
                 next[j]->count += 1;
                 p = next[j];
                 next = p->nextNode;
                 break;
             }
         }
         if(j == len)
             break;
    }
    if(i == word.size())
        p->isEnd = true;
    else{
        for(;i < word.size(); i++)
        {
            TreeNode* node = new TreeNode(1, word[i], false);
            p->nextNode.push_back(node);
            p = node;
        }
        p->isEnd = true;
    }
}

int Trie::searchWord(string word)
{
    vector<struct TreeNode*> next = head->nextNode;
    TreeNode* p = head;
    int i,j;

    for(i = 0; i < word.size(); i++)
    {
         int len = next.size();
         for(j = 0; j < len; j++)
         {
             if(next[j]->a == word[i])
             {
                 p = next[j];
                 next = p->nextNode;
                 break;
             }
         }
         if(j == len)
             return 0;
    }

    return p->count;
}

int main()
{
    Trie tree;
//    tree.addWord("app");
//    tree.addWord("apple");
//    tree.addWord("add");
//    tree.addWord("appart");
//    cout<<tree.searchWord("a");

    int n,m;
    int i,j;
    string word;
    cin>>n;
    for(i = 0; i < n; i++)
    {
        cin>>word;
        tree.addWord(word);
    }
    cin>>m;
    for(j = 0; j < m; j++)
    {
        cin>>word;
        cout<<tree.searchWord(word)<<endl;
    }

    return 0;
}

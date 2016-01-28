#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head==NULL)
            return head;
        ListNode* pre = head;
        ListNode* cur = head->next;
        ListNode* next = NULL;
        while(cur)
        {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        head->next = NULL;
        head = pre;
        return head;
    }
};

void output(ListNode* head)
{
    while(head)
    {
        cout<<head->val<<" ";
        head = head->next;
    }
    cout<<endl;
}

int main()
{
    ListNode head(1);
    ListNode n2(2);
    head.next = &n2;
    output(&head);
    Solution s;
    ListNode* newhead = s.reverseList(&head);
    output(newhead);

}

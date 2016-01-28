
#include<iostream>
using namespace std;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL)
            return head;

        ListNode* p = head;
        ListNode* next = p->next;
        while(next)
        {
            if(next->val == p->val)
            {
                p->next = next->next;
                next = next->next;
            }
            else{
                p = p->next;
                next = p->next;
            }
        }

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
    ListNode n2(1);
    ListNode n3(1);
    ListNode n4(2);
    head.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    output(&head);
    Solution s;
    ListNode* newhead = s.deleteDuplicates(&head);
    output(newhead);

}

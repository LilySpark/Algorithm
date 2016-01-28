#include<iostream>

using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head;

        if(l1 == NULL && l2 == NULL)
            head = NULL;
        else if(l1 == NULL)
            head = l2;
        else if(l2 == NULL)
            head = l1;
        else{
            if(l1->val < l2->val){
                head = l1;
                l1 = l1->next;
            }
            else{
                head = l2;
                l2 = l2->next;
            }
            ListNode* p = head;
            while(l1 && l2)
            {
                    if(l1->val < l2->val)
                    {
                        p->next = l1;
                        p = p->next;
                        l1 = l1->next;
                    }
                    else{
                        p->next = l2;
                        p = p->next;
                        l2 = l2->next;
                    }
            }
            if(l1==NULL)
                p->next = l2;
            else
                p->next = l1;

        }
        return head;

    }
};

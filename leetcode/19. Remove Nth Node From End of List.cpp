#include <iostream>

using namespace std;

struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len = 0;
        ListNode* p = head;
        while(p){
            len++;
            p = p->next;
        }
        p = head;
        int i = 0;
        while(i < len-n -1){
            i++;
            p = p->next;
        }
        if(len-n > 0)
            p->next = p->next->next;
        else
            head = head->next;

        return head;
    }
};


class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *s,*p = new ListNode(0);
        s=head;
        p->next=head;
        while(n-- && s!=NULL)
            s=s->next;

        while(s!=NULL){
            s=s->next;
            p=p->next;
        }
        if(p->next==head){
            head=head->next;
        }else{
            p->next=p->next->next;
        }
        return head;
    }
};

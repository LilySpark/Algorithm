#include <iostream>


using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
/*
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        while(head && head->val == val)
            head = head->next;

        ListNode* p = head;

        while(p && p->next)
        {
            if(p->next->val== val)
                p->next = p->next->next;
            else
                p = p->next;
        }
        return head;
    }
};
*/
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* p = dummy;

        while(p->next)
        {
            if(p->next->val == val)
                p->next = p->next->next;
            else
                p = p->next;
        }
        return dummy->next;
    }
};




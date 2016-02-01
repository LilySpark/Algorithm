#include <iostream>
#include <vector>
using namespace std;


struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head == NULL)
            return true;
        ListNode* pre = head;
        ListNode* next = head->next;
        head->next = NULL;
        vector<int> vals;
        vals.push_back(head->val);
        while(next)
        {
            vals.push_back(next->val);
            ListNode* tmp = next->next;
            next->next = pre;
            pre = next;
            next = tmp;
        }
        ListNode* p = pre;
        int i = 0;
        while(p && i < vals.size())
        {
            if(p->val!=vals[i])
                return false;
        }
        return true;
    }
};

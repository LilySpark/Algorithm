
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode* root = head;
        if(head==NULL)
            return head;
        ListNode* next = head->next;
        int i = 1;
        while(head->next)
        {
            ListNode* tmp = head->next;
            head->next = head->next->next;
            head = tmp;
            i++;
        }
        if(i%2)
            head->next = next;
        else{
            head = root;
            while(head->next)
                head = head->next;
            head->next = next;
        }
        return root;
    }
};

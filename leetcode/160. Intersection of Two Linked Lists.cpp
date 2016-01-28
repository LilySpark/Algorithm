#include <iostream>

using namespace std;


/*
    For example, the following two linked lists:
    Write a program to find the node at which the intersection of two singly linked lists begins.
A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗
B:     b1 → b2 → b3
begin to intersect at node c1.

*/

struct ListNode {
    int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *pa=headA,*pb=headB;
        int lengthA=0,lengthB=0;
        while(pa)
            {pa=pa->next;lengthA++;}
        while(pb)
            {pb=pb->next;lengthB++;}

        if(lengthA<=lengthB){
            int n=lengthB-lengthA;
            pa=headA;pb=headB;
            while(n--) {pb=pb->next;}
        }else{
            int n=lengthA-lengthB;
            pa=headA;pb=headB;
            while(n--) {pa=pa->next;}
        }

        while(pa!=pb){
            pa=pa->next;
            pb=pb->next;
        }
        return pa;
    }
};

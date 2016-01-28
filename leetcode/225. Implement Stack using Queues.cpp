#include <iostream>
#include <queue>
using namespace std;

class Stack {
public:
    // Push element x onto stack.
    queue<int> q1;
    queue<int> q2;
    void push(int x) {
        q1.push(x);
    }

    // Removes the element on top of the stack.
    void pop() {
        if(q1.size()==1)
            q1.pop();
        else{
            while(q1.size() > 1){
                q2.push(q1.front());
                q1.pop();
            }
            q1.pop();
            while(q2.size() > 0){
                q1.push(q2.front());
                q2.pop();
            }
        }
    }
/*
    // Get the top element.
    int top() {
        return q1.back();
    }
*/
    int top() {
        if (q1.size() == 1) return q1.front();
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
        int temp = q1.front();
        q2.push(q1.front());
        q1.pop();
        while (q2.size() > 0) {
            q1.push(q2.front());
            q2.pop();
        }
        return temp;
    }

    // Return whether the stack is empty.
    bool empty() {
        return q1.empty();
    }
};

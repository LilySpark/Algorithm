#include <iostream>
#include <stack>
using namespace std;


class MinStack {
private:
    stack<int> s;
    stack<int> mins;
public:
    void push(int x) {
        s.push(x);
        if(mins.empty())
            mins.push(x);
        else if(x <= mins.top())
            mins.push(x);
    }

    void pop() {
        if(s.top() == mins.top())
            mins.pop();
        s.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
       return mins.top();
    }
};

int main()
{
    return 0;
}

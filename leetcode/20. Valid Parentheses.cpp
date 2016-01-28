#include <iostream>
#include <stack>
#include <map>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> par;
        map<char,char> parmap;
        parmap['('] = ')';
        parmap['['] = ']';
        parmap['{'] = '}';

        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] == '{' or s[i] == '(' or s[i] == '[')
                par.push(s[i]);
            else{
                if(!par.empty())
                {
                    if(parmap[par.top()] == s[i])
                        par.pop();
                    else
                        return false;
                }
                else
                    return false;
            }
        }
        if(par.empty())
            return true;
        else
            return false;

    }
};

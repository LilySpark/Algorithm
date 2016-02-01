#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string res = "";
        int carry = 0;
        int la = a.size();
        int lb = b.size();
        int maxlen = max(la, lb);
        for(int i = 0; i < maxlen; i++)
        {
            int x = i < la ? a[la-1-i]-'0' : 0;
            int y = i < lb ? b[lb-1-i]-'0' : 0;
            int sum = x + y + carry;
            carry = sum/2;
            if(sum%2)
                res =  "1" + res;
            else
                res = "0" + res;
        }
        if(carry > 0)
            res = "1" + res;

        return res;
    }
};

int main()
{
    Solution s;
    cout<<s.addBinary("11","1");
}

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1)
            return s;
        string res;
        int l = s.size();
        int d = (numRows-1)*2;
        for(int j = 0; j < l; j+=d)
            res += s[j];

        for(int i = 1; i < numRows-1; i++)
        {
            int j = i;
            int flag = 0;
            while(j < l)
            {
                res += s[j];
                int k = j + d - 2*i;
                if(k < l)
                    res += s[k];
                else
                    break;
                j += d;
            }
        }
        for(int j = numRows-1; j < l; j+=d)
            res += s[j];

        return res;
    }
};

int main()
{
    Solution s;
    cout<<s.convert("PAYPALISHIRING",3);
}

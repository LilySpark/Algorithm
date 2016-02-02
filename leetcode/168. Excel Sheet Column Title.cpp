#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string convertToTitle(int n) {
        string res = "";
        char c[1];
        while(n)
        {
            res = string(1,'A' + (n-1)%26) + res;
            n = (n-1)/26;
        }
        return res;
    }
};

class Solution {
public:
    string convertToTitle(int n) {
        string res="";
        while(n)
        {
            res += ('A' + (n-1)%26);
            n = (n-1)/26;
        }
        string result;
        for(int i = res.size()-1; i >= 0; i--)
            result += res[i];  //result = result + res[i]³ö´í
        return result;
    }
};

int main()
{
    Solution s;
    cout<<s.convertToTitle(28)<<endl;

    return 0;
}

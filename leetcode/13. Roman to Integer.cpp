#include <iostream>
#include <map>
#include <string>

using namespace std;


//即I（1）、V（5）、X（10）、L（50）、C（100）、D（500）和M（1000）

class Solution {
public:
    int romanToInt(string s) {
        map<char,int> romanMap({{'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}});

        int sum = 0;

        for(int i = 0; i < s.size(); i++)
        {
            if(romanMap.find(s[i]) == romanMap.end())
                return 0;
            sum += romanMap[s[i]];
            if(i!=0 && romanMap[s[i]] > romanMap[s[i-1]])
                sum -= romanMap[s[i-1]]*2;
        }
        return sum;
    }
};

int main()
{
    Solution s;
    cout<<s.romanToInt("XCIX");
}

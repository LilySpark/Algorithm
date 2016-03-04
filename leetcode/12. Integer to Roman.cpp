#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string intToRoman(int num) {
         string res = "";
         vector<vector<string>> roman({{"","I","II","III","IV","V","VI","VII","VIII","IX"},
                                      {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"},
                                      {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"},
                                      {"","M","MM","MMM"}});

        int digit = 0;
        while(num > 0)
        {
            res = roman[digit++][num%10] + res;
            num = num/10;
        }
        return res;
    }
};

int main()
{
    Solution s;
    cout<<s.intToRoman(249)<<endl;
}

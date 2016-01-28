#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
using namespace std;

class Solution {
public:
    string getHint(string secret, string guess) {
        map<int, int> digitMap;
        int bulls = 0;
        int common = 0;
        for(int i = 0; i < secret.size(); i++)
        {
            if(secret[i] == guess[i])
                bulls++;
            digitMap[secret[i]]++;

        }

        for(int i = 0; i < guess.size(); i++)
            if(digitMap.find(guess[i])!=digitMap.end() && digitMap[guess[i]] > 0)
            {
                digitMap[guess[i]]--;
                common++;
            }

        int cows = common - bulls;
        char temp[100];
        sprintf(temp, "%dA%dB", bulls,cows);
        string res(temp);

        return res;
    }
};

int main()
{
    Solution s;
    string secret("1123");
    string guess("0111");
    cout<<s.getHint(secret,guess);

    return 0;

}


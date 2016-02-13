#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string str) {
        map<char, string> csmap;
        map<string, char> scmap;

        vector<string> strv;
        for(int j = 0; j < str.size(); j++)
        {
            string s;
            while(j < str.size() && str[j]!=' ')
                s += str[j++];
            strv.push_back(s);
        }
        if(pattern.size()!=strv.size())
            return false;

        for(int i = 0; i < pattern.size(); i++)
        {
            if(csmap.find(pattern[i])!= csmap.end()){
                if(csmap[pattern[i]] != strv[i])
                    return false;
            }
            else{
                if(scmap.find(strv[i])!= scmap.end()){
                    if(scmap[strv[i]] != pattern[i])
                        return false;
                }
                else
                {
                    csmap[pattern[i]] = strv[i];
                    scmap[strv[i]] = pattern[i];
                }
            }
        }

        return true;
    }
};

int main()
{
    Solution sol;
    string s("abba");
    string t("dog apple apple dog");

    cout<<sol.wordPattern(s,t);
    return 0;
}

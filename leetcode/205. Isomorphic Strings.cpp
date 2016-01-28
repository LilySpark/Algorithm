#include <iostream>
#include <map>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size()!=t.size())
            return false;
        int l = s.size();
        map<char, char> stmap;
        map<char, char> tsmap;
        for(int i = 0; i < l; i++)
        {
            if(stmap.find(s[i])!= stmap.end()){
                if(stmap[s[i]] != t[i])
                    return false;
            }
            else{
                if(tsmap.find(t[i])!= tsmap.end())
                {
                    if(tsmap[t[i]] != s[i])
                        return false;
                }
                else{
                    stmap[s[i]] = t[i];
                    tsmap[t[i]] = s[i];
                }
            }
        }
        return true;
    }
};


int main()
{
    Solution sol;
    string s("ab");
    string t("aa");
    cout<<sol.isIsomorphic(s,t);
    return 0;
}

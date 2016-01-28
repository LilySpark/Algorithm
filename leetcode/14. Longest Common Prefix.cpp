
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {

        string prefix;
        if(strs.size()==0)
            return "";
        if(strs.size()==1)
            return strs[0];

        int minlen = strs[0].size();
        for(int i = 1 ; i < strs.size(); i++)
            if(minlen > strs[i].size())
                minlen = strs[i].size();

        for(int j = 0; j < minlen; j++)
        {
            string str = strs[0];
            int i;
            for(i = 1; i < strs.size(); i++)
                if(strs[i][j] != str[j])
                    break;
            if(i == strs.size())
                prefix.append(1,str[j]);
            else
                break;
        }
        return prefix;
    }
};


int main(){
    Solution s;
    vector<string> strs;
    strs.push_back("aca");
    strs.push_back("cba");
  //  strs.push_back("c");
    cout<<s.longestCommonPrefix(strs)<<endl;


}




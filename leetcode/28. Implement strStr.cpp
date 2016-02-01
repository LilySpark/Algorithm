#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int i = 0;
        int j = 0;
        int index = -1;
        if(!needle.size())
            return 0;

        while(i < haystack.size() && j < needle.size())
        {
            if(haystack[i] == needle[j]){
                if(j==0)
                    index = i;
                i++;
                j++;
            }
            else{
                if(j > 0){
                    j = 0;
                    i = index+1;
                }
                else
                    i++;
            }
        }
        if(j == needle.size())
            return index;
        else
            return -1;
    }
};

int main()
{
    Solution s;
    cout<<s.strStr("mississippi","issip")<<endl;
}

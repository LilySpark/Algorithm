#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int i = 0;
        int j = 0;
        string v1,v2;
        int i1,i2;
        while(i < version1.size() || j < version2.size())
        {
            v1 = "";
            i1 = 0;
            while(i < version1.size() && version1[i]!='.')
                v1 += version1[i++];
            i1 = atoi(v1.c_str());

            v2 = "";
            i2 = 0;
            while(j < version2.size() && version2[j]!='.')
                v2 += version2[j++];
            i2 = atoi(v2.c_str());

            if(i1 > i2)
                return 1;
            else if(i1 < i2)
                return -1;
            i++;
            j++;
        }
        return 0;
    }
};

int main()
{
    Solution s;

    cout<<s.compareVersion("1.2","1.10")<<endl;
    cout<<s.compareVersion("1.1","1.10")<<endl;
    cout<<s.compareVersion("1.1","1.1.0")<<endl;
    cout<<s.compareVersion("1.1","1.1.2")<<endl;

    return 0;

}

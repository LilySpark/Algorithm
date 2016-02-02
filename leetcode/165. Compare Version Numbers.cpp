#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        float f1 = atof(version1.c_str());
        float f2 = atof(version2.c_str());
       // cout<<f1<<" "<<f2<<endl;
        if(f1 > f2)
            return 1;
        else if(f1 == f2)
            return 0;
        else
            return -1;
    }
};

int main()
{
    Solution s;

    cout<<s.compareVersion("1.2","2.5");
    return 0;
}

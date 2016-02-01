#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
/*
    string to_string(int x)
    {
        stringstream s;
        s << x;
        string str = s.str();
        return str;

    }
    */
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        if(nums.size() == 0)
            return res;

        int low = nums[0];
        int high = nums[0];
        string s;
        for(int i = 1; i < nums.size(); i++)
        {

            if(nums[i] - nums[i-1] != 1)
            {
                high = nums[i-1];
                if(high!=low)
                    res.push_back(to_string(low)+"->"+to_string(high));
                else
                    res.push_back(to_string(low));
                low = nums[i];
            }
        }
        if(nums[nums.size()-1]!=low)
            res.push_back(to_string(low)+"->"+to_string(nums[nums.size()-1]));
        else
            res.push_back(to_string(low));

        return res;
    }
};


int main()
{
    Solution s;
    vector<int> v{0,1,2,4,5,7};
    vector<string> res = s.summaryRanges(v);
    for(int i = 0; i < res.size(); i++)
        cout<<res[i]<<" ";

}





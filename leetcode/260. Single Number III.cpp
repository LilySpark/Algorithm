#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
/*
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> singles;
        int i;
        int len = nums.size();
        for(i = 0; i < len-1; i++)
        {
            if(nums[i]!=nums[i+1])
                singles.push_back(nums[i]);
            else
                i++;
        }
        if(i==len-1)
            singles.push_back(nums[len-1]);

        return singles;
    }
};
*/

/* 最后的result是两个不同的数的异或，记录了两个数不同的地方，一定有一个置位为1，
   随意找一个置位，如最右边第一个置位，把所有该位为1的异或，则结果为其中一个数a,因为其他相同的数异或后为0

   a^b = c
   a^c = b
   b^c = a

 */
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int result = 0;
        int len = nums.size();
        for(int i = 0; i < len; i++)
            result ^= nums[i];

        int lastbits = result & (~(result-1));
        int a = 0;
        for(int i = 0; i < len; i++)
            if(lastbits & nums[i])
                a ^= nums[i];

        int b = a ^ result;
        vector<int> singles{a,b};

        return singles;
    }
};

int main()
{
    Solution s;
    vector<int> nums{1,1,2,2,3,4,5,5};
    vector<int> singles =  s.singleNumber(nums);
    cout<<singles[0]<<" "<<singles[1]<<endl;
}

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        map<int, int> numcount;
        for(int i = 0; i < nums.size(); i++)
            numcount[nums[i]]++;

        for(int i = 0; i < nums.size(); i++)
            if(numcount[nums[i]] == 1)
                return nums[i];
    }
};



class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for(int i = 0; i < nums.size(); i++)
            result = result ^ nums[i];

        return result;
    }
};


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int result = 0;
        int k = 1;
        for(int i = 0; i < nums.size(); i++)
        {
             result += nums[i]*k;
             k = k*(-1);
        }
        return result;
    }
};

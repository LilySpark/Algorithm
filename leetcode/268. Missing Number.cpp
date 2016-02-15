#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/*先排个序，逐个比较，不等的直接return*/
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int len = nums.size();
        for(int i = 0; i < nums.size(); i++)
            if(nums[i] != i)
                return i;

        return nums.size();
    }
};


/*
 等差数列先求得总和，然后减去给定的队列，剩下的值就是缺失值。
*/
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int sum = n*(n+1)/2;
        for(int i = 0; i < nums.size(); i++)
            sum -= nums[i];

        return sum;
    }
};

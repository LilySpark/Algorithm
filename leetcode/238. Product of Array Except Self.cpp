#include <iostream>
#include <vector>

using namespace std;

/*
维持两个数组, left[] and right[]. 分别记录第i个元素左边相加的和left[i] and 右边相加的和right[i].
那么结果res[i]即为 left[i]*right[i]. follow up 要求O(1)空间.
利用返回的结果数组,先存right数组. 再从左边计算left,同时计算结果值, 这样可以不需要额外的空间.

*/


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result(nums.size(),1);

        for(int i = nums.size() - 2; i >= 0; i--)
            result[i] = result[i+1] * nums[i+1];

        int left = 1;
        for(int i = 0; i < nums.size(); i++)
        {
            result[i] *= left;
            left *= nums[i];
        }

        return result;
    }
};

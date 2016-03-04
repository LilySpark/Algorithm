#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
设所求的上升序列为 x1,x2,x3 （x1<x2<x3）
初始时设置x1 = x2 = INT_MAX ，然后遍历数组
num <= x1: 此时将x1设置为num
若 x1 < num <= x2，则把x2设置为num
x1 < x2 < num  说明有解，返回true即可
简单的说，上述的过程就是不断的缩小x1和x2，（并且保证x1 < x2）看看是否有第三个数比x2大。
*/

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int len = nums.size();
        int x1 = 0x7fffffff;
        int x2 = 0x7fffffff;
        for(int i = 0; i < nums.size(); i++)
        {
            if(nums[i] <= x1)
                x1 = nums[i];
            else if(nums[i] <= x2)
                x2 = nums[i];
            else
            {
                cout<<x1<<" "<<x2<<" "<<nums[i]<<endl;
                return true;
            }

        }
        return false;
    }
};

int main()
{
    Solution s;
    vector<int> nums({3,4,1,5});
    cout<<s.increasingTriplet(nums);
}

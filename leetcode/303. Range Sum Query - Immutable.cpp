#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class NumArray {
private:
    vector<int> sums;
    vector<int> num;
public:
    NumArray(vector<int> &nums) {
        if(nums.size())
        {
            sums.push_back(nums[0]);
            num = nums;
            for(int i = 1; i < nums.size(); i++)
                sums.push_back(sums[i-1] + nums[i]);
        }
    }

    int sumRange(int i, int j) {
        return sums[j] - sums[i] + num[i];
    }
};

int main()
{
    vector<int> nums{1,2,3,4,5};
    NumArray numArray(nums);
    cout<<numArray.sumRange(0, 1)<<endl;
    cout<<numArray.sumRange(1, 2)<<endl;

    return 0;
}


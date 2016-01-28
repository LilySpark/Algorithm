
#include<iostream>
#include<algorithm>

using namespace std;
class Solution {
public:
    int findNextNonzero(int next,vector<int>& nums)
    {
        while(nums[next]==0 && next < nums.size())
        {
            next++;
        }
        return next;
    }
    void moveZeroes(vector<int>& nums) {
        int m = nums.size();
        int start;
        int next;
        for(start=0;start < m-1;start++)
        {
            if(nums[start]==0 ){
                next = findNextNonzero(start,nums);
                if(start<next && next<m){
                    int tmp = nums[start];
                    nums[start] = nums[next];
                    nums[next] = tmp;
                }
            }
        }
    }
};

int main()
{
    vector<int> nums{0, 1, 0, 3, 12};
    Solution solution;
    solution.moveZeroes(nums);
    for(int i=0; i<nums.size(); i++)
        cout<<nums[i]<<" ";
    cout<<endl;
}

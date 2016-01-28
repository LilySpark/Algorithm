#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {

        if(nums.size() <= 1)
            return nums.size();
        int count = 1;
        int a = nums[0];
        vector<int>::iterator iter;
        for(iter=nums.begin()+1; iter != nums.end(); iter++)
        {
            while(iter != nums.end() && *iter==a)
                iter = nums.erase(iter);
            if(iter != nums.end()){
                a = *iter;
                count = count + 1;
            }
            else
                break;
        }
        return count;
    }
};

//It doesn't matter what you leave beyond the new length.
class Solution {
public:
 int removeDuplicates(vector<int> &nums) {
    if(nums.size() < 2)
        return nums.size();
    int len = 1;
    for(int i = 1; i < nums.size(); i++){
        if(nums[i] != nums[i - 1])
            nums[len++] = nums[i];
    }
    return len;
    }
};

int main()
{
    vector<int> a{1,1};
    Solution s;
    int count = s.removeDuplicates(a);
    cout<<"count : "<<count<<endl;
    for(int i=0; i < a.size(); i++)
        cout<<a[i]<<" ";
    cout<<endl;

}

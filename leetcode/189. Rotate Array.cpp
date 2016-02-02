#include <iostream>
#include <vector>
using namespace std;

//O(n) time, O(n) space
/*
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k%n;
        vector<int> p;
        vector<int> q;
        if(k)
        {
            for(int i = n-k; i<n; i++)
                p.push_back(nums[i]);
            for(int i = 0; i<n-k; i++)
                q.push_back(nums[i]);

            for(int i=0; i<k; i++)
                nums[i] = p[i];
            for(int i=k; i<n; i++)
                nums[i] = q[i-k];
        }
    }
};
*/
//O(n) time, O(1) space
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        int tmp1,tmp2 = nums[0];
        int cur = 0;
        int start = 0;
        for(int i = 0; i < n; i++)
        {
            tmp1 = tmp2;
            cur = (cur + k) % n;
            tmp2 = nums[cur];
            nums[cur] = tmp1;
            if(cur == start)
            {
                cur = ++start;
                tmp2 = nums[cur];
            }
        }
    }
};

int main()
{
    Solution s;
    vector<int> nums{1,2,3,4,5,6,7};
    s.rotate(nums, 3);
    for(int i=0; i < nums.size(); i++)
        cout<<nums[i]<<" ";
    cout<<endl;
    return 0;
}

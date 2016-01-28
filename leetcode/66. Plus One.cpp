
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int add = 1;
        vector<int>::iterator iter;
        for(iter=digits.end()-1;iter>=digits.begin();iter--)
        {
            if(add>0)
            {
                int tmp = *iter+add;
                *iter = tmp % 10;
                add =  tmp / 10;
            }
            else
                break;
            if(iter==digits.begin())
                break;
        }
        if(iter==digits.begin() && add > 0)
            digits.insert(iter,add);

        return digits;
    }
};
/*
//题意：一个整数按位存储于一个int数组中，排列顺序为：最高位在digits[0] ，最低位在digits[n-1]，
//例如：98，存储为：digits[0]=9; digits[1]=8;
//解题思路:从数组的最后一位开始加1，需要考虑进位，如果到digits[0]位之后仍然有进位存在,则将进位加上
class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        int a = 1;
        vector<int> ans;
        vector<int>::iterator it;
        for(int i = digits.size() - 1;i >= 0;i--)
        {
            it = ans.begin();
            int tmp = (a + digits[i]) % 10;
            a = (a + digits[i]) / 10;
            ans.insert(it, tmp);
        }
        if(a != 0)
        {
            it = ans.begin();
            ans.insert(it, a);
        }

        return ans;
    }
};
*/
int main()
{
    Solution s;
    vector<int> nums{9,9,9};
    vector<int> plusone = s.plusOne(nums);
    for(int i=0; i < plusone.size();i++)
        cout<<plusone[i]<<" ";
    cout<<endl;
}

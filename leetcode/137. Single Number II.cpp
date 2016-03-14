#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> count;
        for(int i = 0; i < nums.size(); i++)
            count[nums[i]]++;

        for(int i = 0; i < nums.size(); i++)
            if(count[nums[i]] == 1)
                return nums[i];

    }

    int singleNumber2(vector<int>& nums) {
        int result = 0;
        for(int i = 0; i < 32; i++)
        {
            int bits = 1 << i;
            int cnt = 0;
            for(int j = 0; j < nums.size(); j++)
            {
                if(nums[j] & bits)
                    cnt++;
            }
            if(cnt % 3 != 0)
                result |= bits;
        }
        return result;

    }

    int singleNumber3(vector<int>& nums) {
        int ones = 0;
        int twos = 0;
        int threes = 0;
        for(int i = 0; i < nums.size(); i++)
        {
            twos |= (ones & nums[i]);
            ones ^= nums[i];
            threes = ~(ones & twos);
            ones &= threes;
            twos &= threes;
        }
        return ones;
    }


};

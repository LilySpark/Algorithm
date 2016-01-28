#include <iostream>
#include <vector>
#include <math.h>
#include <map>
using namespace std;
/*
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        for(int i = 0; i < nums.size(); i++){
             int s = k + i + 1 < nums.size()?k + i + 1:nums.size();
             for(int j = i+1; j < s; j++)
                if(nums[j] == nums[i] && abs(j-i)<=k)
                    return true;
        }

        return false;
    }
};
*/
/*
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int, vector<int>> sta;
        for(int i = 0; i < nums.size(); i++){
            sta[nums[i]].push_back(i);
        }
        map<int, vector<int>>::iterator iter;
        for(iter=sta.begin(); iter!=sta.end();iter++)
        {
            vector<int> pos = (*iter).second;
            for(int i=0; i < pos.size()-1;i++)
                if(pos[i+1]-pos[i]<=k)
                    return true;
        }

        return false;
    }
};
*/
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int, int> sta;
        for(int i = 0; i < nums.size(); i++){
            if(sta.find(nums[i])!=sta.end() && i - sta[nums[i]] <= k)
                return true;
            else
                sta[nums[i]] = i;
        }

        return false;
    }
};



#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if(!len)
            return 0;

        int values[len][2];
        values[0][0] = 0;
        values[0][1] = nums[0];
        for(int i = 1; i < len; i++)
        {
            values[i][0] = max(values[i-1][0], values[i-1][1]);
            values[i][1] = values[i-1][0] + nums[i];
        }
        return max(values[len-1][0],values[len-1][1]);
    }
};

int main()
{

}

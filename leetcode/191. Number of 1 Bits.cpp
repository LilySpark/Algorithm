class Solution {
public:
    int hammingWeight(uint32_t n) {
        vector<int> remains;
        while(n)
        {
            remains.push_back(n%2);
            n = n/2;
        }
        int sum = 0;
        for(int i=0; i < remains.size(); i++)
           sum+=remains[i];
        return sum;

    }
};

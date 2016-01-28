#include<iostream>
#include<vector>
#include<math.h>
using namespace std;


class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        vector<int> bits;
        int newNum = 0;
        while(n){
            bits.push_back(n%2);
            n = n/2;
        }

        for(int i=0; i < bits.size(); i++){
            cout<<bits[i]<<endl;
            newNum += bits[i] * pow(2,31-i);
        }

        return newNum;

    }
};



class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t result=0;
        for(int j=0;j<32;j++){
            if(n&1){
                result += pow(2.0,31-j);
            }
            n = n>>1;
        }
        return result;
    }
};

//(((a*2+b)*2+c)*2+d)*2+e
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        int num=0;
        for(int i=0; i<32; i++){
            num = num<<1 | n&1;
            n>>=1;
        }
        return num;
    }
};

int main()
{
    uint32_t num = 43261596;
    Solution s;
    cout<<s.reverseBits(num);
}

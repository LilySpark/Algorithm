#include <iostream>

using namespace std;


//incase overflow, max 32-bit int is 21474883647
class Solution {
public:
    int reverse(int x) {
        int sum = 0;
        while(x)
        {
            if(abs(sum) > 214748364)
                return 0;
            sum = sum*10 + x%10;
            x = x/10;
        }
        return sum;
    }
};

int main(){
    Solution s;
    cout<<s.reverse(1534236469)<<endl;
}

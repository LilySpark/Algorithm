#include<iostream>
using namespace std;

class Solution {
public:
    int addDigits(int num) {
        int sum=num;
        while(sum/10)
        {
            num = sum;
            sum = 0;
            while(num)
            {
                sum += num%10;
                num = num/10;
            }
        }
        return sum;
    }
};

int main()
{
    Solution solution;
    cout<<solution.addDigits(38)<<endl;
    return 0;
}

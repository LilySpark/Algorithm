#include<iostream>
#include<math.h>
using namespace std;


class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n==0)
            return false;
        while(n%3==0)
            n=n/3;
        return n==1;
    }
};

class Solution {
public:
    bool isPowerOfThree(int n) {
        double res = log10(n) / log10(3);  //有精度问题，不要用log
        return (res - int(res) == 0) ? true : false;
    }
};

//直接枚举
class Solution {
public:
    bool isPowerOfThree(int n) {
        return (n == 1 || n == 3 || n == 9 || n == 27 || n == 81 || n == 243 || n == 729 || n == 2187 || n == 6561 || n == 19683 || n == 59049 || n == 177147 || n == 531441 || n == 1594323 || n == 4782969 || n == 14348907 || n == 43046721 || n == 129140163 || n == 387420489 || n == 1162261467);
    }
};

//任何一个3的i次方一定能被int型里最大的3的i次方整除
class Solution {
public:
    bool isPowerOfThree(int n) {
        return n>0?!(1162261467 % n):0;
    }
};

int main()
{
    Solution s;
    cout<<s.isPowerOfThree(9)<<endl;
    cout<<s.isPowerOfThree(8)<<endl;

    return 0;
}

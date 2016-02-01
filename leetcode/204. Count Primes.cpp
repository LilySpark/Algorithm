#include <iostream>
#include <math.h>
using namespace std;

//n > 0
/*
我试图在遍历的过程中保存之前所有的质数，然后对于对于一个自然数 N：
只需用小于 N 的素数去除就可以了。
而且，不必用从 2 到 N一1 的所有质数去除，只需用小于等于N−−√（根号N）的所有素数去除就可以了。
*/

class Solution {
public:
    int countPrimes(int n) {
        int count = 0;
        vector<int> primes;  // 保存质数
        primes.push_back(3);
        primes.push_back(5);
        primes.push_back(7);
        for(int i=9; i<n; i=i+2)  // 只考虑奇数
        {
            bool flag = true;
            for(int j=0; j<primes.size()&&primes[j]<=pow(i,0.5); ++j)
                if(i%primes[j] == 0)
                {
                    flag = false;
                    break;
                }

            if(flag) {
                ++count;
                primes.push_back(i);
            }
        }
        return count+4;  // 加上前四个
    }
};





class Solution {
public:
    int countPrimes(int n) {
        bool *Del = new bool[n]; // 标记是否被划去
        Del[2] = false;

        for(int i=3; i<n; ++i)
            if(i%2 == 0)
                Del[i] = true;  // 2的倍数全部划去
            else
                Del[i] = false;

        for(int i=3; i<n; i+=2)
            if(!Del[i])  // 之后第一个未被划去
            {
                if(i*i>n)  break;  // 当前素数的平方大于n，跳出循环
                for(int j=2; i*j<n; ++j)
                    Del[i*j] = true;
            }

        int count = 0;
        for(int i=2; i<n; ++i)
            if(!Del[i])
                ++count;

        delete [] Del;
        return count;
    }
};

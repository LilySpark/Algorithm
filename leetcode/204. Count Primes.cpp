#include <iostream>
#include <math.h>
using namespace std;

//n > 0
class Solution {
public:
    bool isPrime(int n)
    {
        if(n == 1)
            return false;

        for(int i = 2; i <= sqrt(n); i++)
            if(n%2 == 0)
                return false;
        return true;
    }
    int countPrimes(int n) {
        int count = 0;
        for(int i = 2; i < n; i++)
            if(isPrime(i))
                count++;
        return count;
    }
};

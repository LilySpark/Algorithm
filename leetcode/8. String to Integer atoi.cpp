#include <iostream>
#include <string>
#include <cstdlib>
#include <limits.h>
using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        int i = 0;
        int neg = 1;
        while(i < str.size() && str[i] == ' ')
            i++;
        if(i==str.size())
            return 0;

        if(str[i] == '+')
            i++;
        else if(str[i] == '-')
        {
            i++;
            neg = -1;
        }
        int result = 0;
        while(i < str.size() && str[i] <= '9' && str[i] >= '0')
        {
            int digit = str[i] - '0';
            if(result > INT_MAX/10)
                return (neg > 0) ? INT_MAX : INT_MIN;
            result = result*10;
            if(result > INT_MAX - digit)
                return (neg > 0) ? INT_MAX : INT_MIN;
            result += digit;
            i++;
        }
        return neg*result;
    }
};

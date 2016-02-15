#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

/*
小于等于n的每个数字，各有几个无重复的因子，因子包括1及其自身
因子的个数为奇数个时，n轮过后就是on,返回有几个是奇数个因子的

而因子都是成对出现的，之所以出现了奇数个因子，是因为有个因子的平方＝这个数
即此数为完全平方数

对n开平方，则小于等于n的 完全平方数 的个数 就是n开方后取整
*/


class Solution {
public:
    int bulbSwitch(int n) {
        return (int)sqrt(n);
    }
};

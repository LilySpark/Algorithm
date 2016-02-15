#include <iostream>
#include <vector>
using namespace std;

/*
    本题由于是可以操作任意次数，只为获得最大收益，而且对于一个上升子序列，
    比如：[5, 1, 2, 3, 4]中的1, 2, 3, 4序列来说，对于两种操作方案：
    1 在1买入，4卖出
    2 在1买入，2卖出同时买入，3卖出同时买入，4卖出
    这两种操作下，收益是一样的。
    所以可以从头到尾扫描prices，如果price[i] – price[i-1]大于零则计入最后的收益中。

    即贪心法

*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        for(int i = 1; i < prices.size(); i++)
        {
            if(prices[i] > prices[i-1])
                profit += prices[i] - prices[i-1];
        }
        return profit;
    }
};

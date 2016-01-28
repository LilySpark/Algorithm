
class Solution {
public:
    bool isHappy(int n) {

        if(n==1) return true;
        map<int,int> nums;

        while(n>0){
            int number = 0;
            # 计算一个数各个位的平方和
            while(n){
                number += (n % 10) * (n % 10);
                n/=10;
            }

            if(number == 1)
                return true;
            else if(nums.find(number)!=nums.end())
                return false;
            n = number;
            nums[n] = 1;
        }
    }
};


class Solution {
public:
    bool isHappy(int n) {
        while(n>6){
            int next = 0;
            while(n){
                next+=(n%10)*(n%10);
                n/=10;
            }
            n = next;
        }
        return n==1;
    }
};

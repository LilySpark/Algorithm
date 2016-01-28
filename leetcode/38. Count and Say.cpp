#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdio.h>
using namespace std;


class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) {
            return "1";
        } else {
            string output = countAndSay(n - 1);
            string result = "";
            int index = 0;
            while (index < output.size()) {
                char current = output[index];
                int cursor = index;
                int count = 0;
                while (output[cursor] == current && cursor < output.size())
                {
                    cursor++;
                    count++;
                }
                char number = count + '0';
                result += number;
                result += current;
                index += count;
            }
            return result;
        }
    }
};

int main()
{
    Solution s;
    cout<<s.countAndSay(4)<<endl;
}

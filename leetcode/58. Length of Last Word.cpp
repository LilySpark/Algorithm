#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int l = s.size();
        int index = -1;
        int i = l-1;

        //先去掉末尾的零
        while(i >=0 && s[i]==' ')
            i--;
        if(i < 0) //空字符串
            return 0;

        for(int j = i; j >= 0; j--)
            if(s[j] == ' '){
                index = j;
                break;
            }

        return i-index;
    }
};


//思路首先：简单模拟思想，去掉尾部的空格并统计是字符的个数直到再次遇到空格就停止统计
class Solution {
public:
    int lengthOfLastWord(string s) {
        int strLen=s.size();
        int len=0;
        int i=0;
        while(s[strLen-i-1]==' ')
            i++;
        for(;i<strLen;i++)
        {
            if(s[strLen-i-1]>='A'&&s[strLen-i-1]<='Z' || s[strLen-i-1]>='a'&&s[strLen-i-1]<='z' )
                len++;
            else
                break;
        }
        return len;
    }
};

int main()
{
    string s = "Hello World";
    Solution slu;
    cout<<slu.lengthOfLastWord(s)<<endl;
}

#include <iostream>
#include <string>

using namespace std;

//considering only alphanumeric(字母数字的) characters and ignoring cases.
class Solution {
public:
    bool isPalindrome(string s) {
        string news;
        if(s.size()==0 || s.size()==1)
            return true;
        int i = 0;
        int j = s.size();
        while(i <= j)
        {
            while(i < s.size() && !(s[i] >= 'a'&& s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= '0' && s[i] <= '9'))
                i++;
            while(j >= 0 && !(s[j] >= 'a'&& s[j] <= 'z') && !(s[j] >= 'A' && s[j] <= 'Z') && !(s[j] >= '0' && s[j] <= '9'))
                j--;

            if(i <= j)
            {
                if(s[i] >= 'A'&& s[i] <= 'Z')
                    s[i] = s[i]-'A' + 'a';

                if(s[j] >= 'A'&& s[j] <= 'Z')
                    s[j] = s[j]-'A' + 'a';

                if(s[i]!=s[j])
                    return false;
                else{
                    i++;
                    j--;
                }
            }

        }
        return true;
    }
};

int main(){
    Solution s;
    cout<<s.isPalindrome("A man, a plan, a canal: Panama")<<endl;
    cout<<s.isPalindrome("0P");
}

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int longestPalindrome(string s)
{
    string s1;
    s1.resize(2*s.size()+3);
    s1[0]='$';
    s1[1]='#';
    for(int i = 0; i < s.size(); i++)
    {
        s1[2*(i+1)] =  s[i];
        s1[2*(i+1)+1] =  '#';
    }
    s1[2*s.size()+2] = '^';

    int n = s1.size();
    vector<int> p(n,0);
    int id = 0;
    int longest = 0;
    int mx = 0;
    for(int i = 1; i < n-1; i++)
    {
        mx = id+p[id];
        if(mx > i)
            p[i] = min(p[2*id-i], mx - i);
        else
            p[i] = 1;
        while(s1[i+p[i]] == s1[i-p[i]])
            p[i]++;

        if(p[i] + i > mx)
            id = i;

        longest = max(longest, p[i]);

    }
    return longest - 1;

}

int main()
{
    int n;
    string s;
    cin>>n;
    while(n--)
    {
        cin>>s;
        cout<<longestPalindrome(s)<<endl;
    }
    return 0;
}

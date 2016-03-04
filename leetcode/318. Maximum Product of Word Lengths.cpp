#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int maxProduct(vector<string>& words) {
        int maxp = 0;
        int len = words.size();
        vector<int> mask(len, 0);

        for(int i = 0; i < len; i++ )
            for(int j = 0; j < words[i].length(); j++)
                mask[i] = mask[i] | (1 << (words[i][j] - 'a'));

        for(int i = 0; i < len - 1; i++ )
            for(int j = i + 1; j < len; j++)
                if( (mask[i] & mask[j]) == 0)  //别漏了括号
                {
                    int product = words[i].length() * words[j].length();
                    if(maxp < product)
                        maxp = product;
                }

        return maxp;
    }
};

int main()
{
    Solution s;
    vector<string> words({"abcw", "baz", "foo", "bar", "xtfn", "abcdef"});
    for(int i = 0; i < words.size(); i++)
        cout<<words[i]<<endl;

    cout<<s.maxProduct(words);
}

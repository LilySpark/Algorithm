class Solution {
public:
    bool isPalindrome(int x) {
        vector<int> v;
        if(x<0)
            return false;
        while(x)
        {
            v.push_back(x%10);
            x = x/10;
        }
        int size = v.size();
        for(int i=0; i<size/2;i++)
            if(v[i] != v[size-1-i])
                return false;

        return true;
    }
};



//思路首先：简单模拟思想，直接排序查看是否每个数据都是一样的！
//如果是一样的，我们就可以认为两个字符串中某一些字符被易换了位置！
class Solution {
public:
    bool isAnagram(string s, string t) {
            if(s.size()!=t.size())
                return false;
            sort(s.begin(),s.end());
            sort(t.begin(),t.end());
            return s==t;
    }
};


//思路首先：s和t必须拥有相同个数的字符，并且所有字符必须相同
//申请一个数组vecnt来统计字符出现的次数，s中出现的字符则增加对应数组位置的值，t则减少
//如果t中的某个字符没有和s出现相同的次数，那么vecnt中对应位置的值必不为0
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.empty() && t.empty())
            return true;
        if(s.size() != t.size())
            return false;

       vector<int> vecnt(26);
        for(int i=0;i<s.size();i++){
            vecnt[s[i]-'a']++;
            vecnt[t[i]-'a']--;//遍历完数组，如果移位，应该所有值都为0
        }

        for(int i=0;i<26;i++)
            if(vecnt[i] != 0)
                return false;

        return true;
    }
};

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length())
            return false;
        unordered_map<char, int> countsmap;
        for (int i = 0; i < s.size(); i++) {
            countsmap[s[i]]++;
            countsmap[t[i]]--;
        }
        unordered_map<char,int>::iterator ite;
        for(ite=countsmap.begin();ite!=countsmap.end();ite++)
            if(ite->second)
                return false;

        return true;
    }
};

#include<vector>
#include<iostream>

using namespace std;

class Solution {

private:
    vector<int> path;
    int longest = 0;
    int m=0;
    int n=0;
    void findPath(int k, int dep,vector<vector<int> >& matrix);
    bool check(int root,int i, int j,vector<vector<int> >& matrix);

public:
    vector<int> longestPath;
    int longestIncreasingPath(vector<vector<int> >& matrix)
    {
        m = matrix.size();
        if(!m)
            return 0;
        n = matrix[0].size();
        for(int k=0; k<m*n; k++)
            findPath(k,0,matrix);

        return longest;
    }
};

bool Solution::check(int root,int i, int j,vector<vector<int> >& matrix)
{
    if(i>=0 && i<m && j>=0 && j<n)
        if(root < matrix[i][j])
            return true;
    return false;

}

void Solution::findPath(int k, int dep,vector<vector<int> >& matrix)
{
    int i=k/n;
    int j=k%n;
    path.push_back(matrix[i][j]);
    int rows[4] = {i,i,i-1,i+1};
    int cols[4] = {j-1,j+1,j,j};
    int l;
    for(l=0; l < 4; l++)
    {
        if(check(matrix[i][j],rows[l],cols[l],matrix)){
            path.push_back(matrix[rows[l]][cols[l]]);
            k = rows[l]*n + cols[l];
            findPath(k, dep+1, matrix);
        }
    }
    if(longest < dep + 1)
    {
        longest = dep + 1;
        longestPath = path;
    }
    path.pop_back();
}

int main()
{
    int i,j,k;

    vector<vector<int> > matrix{{0,1,2,3,4,5,6,7,8,9},{19,18,17,16,15,14,13,12,11,10},{20,21,22,23,24,25,26,27,28,29},
    {39,38,37,36,35,34,33,32,31,30},{40,41,42,43,44,45,46,47,48,49},{59,58,57,56,55,54,53,52,51,50},
    {60,61,62,63,64,65,66,67,68,69},{79,78,77,76,75,74,73,72,71,70},{80,81,82,83,84,85,86,87,88,89},
    {99,98,97,96,95,94,93,92,91,90},{100,101,102,103,104,105,106,107,108,109},{119,118,117,116,115,114,113,112,111,110},
    {120,121,122,123,124,125,126,127,128,129},{139,138,137,136,135,134,133,132,131,130},{0,0,0,0,0,0,0,0,0,0}};

    int m = matrix.size();
    int n = matrix[0].size();

    cout<<"m "<<m<<endl;
    cout<<"n "<<n<<endl;
    for(i=0; i < m; i++){
        for(j=0; j < n; j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }

    Solution solution;
    int longest = solution.longestIncreasingPath(matrix);
    cout<<"longest path length : "<<longest<<endl;
    for(j=0; j < longest; j++)
        cout<<solution.longestPath[j]<<" "<<endl;
    cout<<endl;

    return  0;
}

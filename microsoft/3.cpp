#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main(void)
{
    int n,m;
    char a;
    cin>>n>>m;
    vector<vector<char> > matrix;
    for(int i = 0; i < n; i++)
    {
        vector<char> line;
        for(int j = 0; j < m; j++)
        {
            cin>>a;
            line.push_back(a);
        }
        matrix.push_back(line);
    }

    int i = 0;
    int j = 0;
    bool right = true;
    int operation = 0;
    while(!(i==n-1&&j==m-1))
    {
        if(right)
        {
            if(j < m && matrix[i][j]=='.')
                j++;
            else
                {
                    right=false;
                }
        }
        if(!right)
        {
            if(i < n && matrix[i][j]=='.')
                i++;
            else
        }


    }


    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int n,m;
vector<int> res;
int numOperation(int i, int j, bool angle, vector<vector<char>>& matrix)
{
    if(i==n-1 && j==m-1)
        return 0;
    int right = 0;
    int bottom = 0;
    if(j < m-1)
    {
        if(angle){
            if(matrix[i][j+1]=='b')
                right += 1;
        }
        else{
            if(i < n-1 && matrix[i+1][j]=='.')
                right += 1;
            if(matrix[i][j+1]=='b')
                right += 1;
        }
    }
    if(i < n-1)
    {
        if(!angle){
            if(matrix[i+1][j]=='b')
                bottom += 1;
        }
        else{
            if(j < m-1 && matrix[i][j+1]=='.')
                bottom += 1;
            if(matrix[i+1][j]=='b')
                bottom +=1;
        }
    }

    if(i<n-1&&j<m-1){
        int rightN;
        int leftN;
        if(i==j+1)
        {
            if(res[i]!=-1)
                rightN = res[i];
            else{
                rightN = right+numOperation(i,j+1,true,matrix);
                res[i] = rightN;
            }
        }
        if(i+1==1)
        {
            if(res[i+1]!=-1)
                leftN = res[i+1];
            else{
                leftN = bottom+numOperation(i+1,j,false,matrix);
                res[i+1] = leftN;
            }
        }


        return min(rightN,leftN);

    }

    if(i == n-1)
        return right+numOperation(i,j+1,true,matrix);
    if(j == m-1)
        return bottom+numOperation(i+1,j,false,matrix);

}

int main(void)
{

    char a;
    cin>>n>>m;
    vector<vector<char> > matrix;
    for(int i = 0; i < n; i++)
        res.push_back(-1);
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

    cout<<numOperation(0,0,true,matrix)<<endl;

    return 0;
}




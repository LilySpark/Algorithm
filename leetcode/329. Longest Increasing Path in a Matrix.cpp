
#include<iostream>

using namespace std;

//int matrix[3][3]={{9,9,4},{6,6,8},{2,1,1}};
int matrix[20][1] = {{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15},{16},{17},{18},{19}};
int m = 20;
int n = 1;
int path[100];
int longestPath[100];
int longest = 0;


bool check(int root,int i, int j)
{
    if(i>=0 && i<m && j>=0 && j<n)
        if(root < matrix[i][j])
            return true;
    return false;

}

void findPath(int k, int dep)
{
    int i=k/n;
    int j=k%n;
    path[dep] = matrix[i][j];
    int rows[4] = {i,i,i-1,i+1};
    int cols[4] = {j-1,j+1,j,j};
    int l;
    for(l=0; l < 4; l++)
    {
        if(check(matrix[i][j],rows[l],cols[l])){
            path[dep+1] = matrix[rows[l]][cols[l]];
            k = rows[l]*n + cols[l];
            findPath(k, dep+1);
        }
    }
    if(longest < dep + 1)
    {
        longest = dep + 1;
        for(int v=0; v <= dep; v++)
            longestPath[v] = path[v];
    }
}

int main()
{
    int i,j,k;

    for(k=0; k<m*n; k++){
        findPath(k,0);
    }
    cout<<"longest path length : "<<longest<<endl;
    for(j=0; j < longest; j++)
        cout<<longestPath[j]<<" "<<endl;
    cout<<endl;

    return  0;
}

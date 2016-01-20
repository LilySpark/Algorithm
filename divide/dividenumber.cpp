#include<iostream>

using namespace std;

int dividenumber(int n,int m)
{
    if(n==1 || m == 1)
        return 1;
    else if(n==m)
        return dividenumber(n,n-1)+1;
    else if(n>m && m>1)
        return dividenumber(n,m-1)+dividenumber(n-m,m);
    else
        return dividenumber(n,n);

}

int main()
{
    int count = dividenumber(6,6);
    cout<<count<<endl;

}

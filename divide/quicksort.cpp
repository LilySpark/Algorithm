#include<iostream>
using namespace std;

void swap(int a[],int i,int j)
{

    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

int partion(int a[], int p, int r)
{
    int i = p;
    int j = r+1;
    int x = a[p];
    while(true)
    {
        while(a[++i] <= x && i < r);

        while(a[--j] > x);

        if(i>=j)
            break;
        else
            swap(a,i,j);
    }
    a[p] = a[j];
    a[j] = x;
    return j;
}

void QuickSort(int a[],int p,int r)
{
    if(p<r)
    {
        int q = partion(a,p,r);
        QuickSort(a,p,q-1);
        QuickSort(a,q+1,r);
    }
}


int main()
{
    int a[] ={3,2,3,1,6,3,9,12,5};
    QuickSort(a,0,8);
    int i = 0;
    for(i=0;i<9;i++)
        cout<<a[i]<<" ";
    cout<<endl;
}



int partition(vector<int>& a, int low, int high)
{
    int i = low -1;
    int j = low;
    int x = a[high];
    while(j < high)
    {
        if(a[j] <= x){
            swap(a[j], a[i+1]);
            i++;
        }
        j++;
    }
    swap(a[high], a[i+1]);
    return i+1;
}

void QuickSort(vector<int>& a, int p, int r)
{
    if(p < r)
    {
        int q = partition(a,p,r);
        QuickSort(a, p, q-1);
        QuickSort(a, q+1, r);
    }
}


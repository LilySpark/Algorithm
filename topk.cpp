#include <iostream>
using namespace std ;
const int N = 8;
const int K = 4;
int partition(int  a[], int low, int high)
{
    int i = low - 1;
    int j = low;
    while(j < high)
    {
         if(a[j] >= a[high])
         {
            swap(a[i+1], a[j]);
            i++;
         }
         j++;
    }
    //最后处理a[high]
    swap(a[i+1], a[high]);
    return i + 1;
}

int findk(int  a[], int low, int high, int k)
{
    if(low < high)
    {
        int q = partition(a, low, high);
        int len = q - low + 1; //表示第几个位置
        if(len == k)
            return q ; //返回第k个位置

        else if(len < k)
            return findk(a, q + 1, high, k - len) ;
        else
            return findk(a, low, q - 1, k) ;
    }
}

int main()
{
    int a[N] = {5 ,2 ,66 ,23, 11 ,1 ,4 ,55};
    findk(a , 0 , N - 1 , K);
    for(int i = 0; i < K; i++)
       cout<<a[i]<<endl;

    system("pause");

    return 0 ;
}

#include <iostream>
using namespace std;
int data[10]={71,18,151,138,160 ,63 ,174, 169 ,79 ,78 };

//以某个节点为根节点的子树进行调整，调整为大顶堆
void max_heapify(int data[],int i,int heapsize)
{
    int l=2*i+1;
    int r=2*i+2;
    int largest=i;
    if(l<heapsize&&data[l]>data[i])
    {
        largest=l;
    }
    if(r<heapsize&&data[r]>data[largest])
    {
        largest=r;
    }
    if(largest!=i)
    {
        int temp=data[largest];
        data[largest]=data[i];
        data[i]=temp;
        max_heapify(data,largest,heapsize);
    }
}

//建堆的过程，通过自底向上地调用max_heapify来将一个数组data【1……n】变成一个大顶堆，
//只需要对除了叶子节点以外的节点进行调整
void bulid_max_heap(int data[],int heapsize)
{　　　　　　　　　　　　　　　　　　　　　　　　　
    for(int i=heapsize/2-1;i>=0;i--)
         max_heapify(data,i,heapsize);
}

//堆排序算法实现主体：先用bulid_max_heap将输入数组构造成大顶堆，
//然后将data【0】和堆的最后一个元数交换，继续进行调整
void heap_sort(int data[],int heapsize)
{　　　　　　　　　　　　　　　　　　　　　　　
     bulid_max_heap(data,heapsize);
     for(int i=heapsize-1;i>0;i--)
     {
         int t=data[0];
         data[0]=data[i];
         data[i]=t;
         max_heapify(data,0,i);

     }
}
int main()
{
    cout<<"堆排序算法实现"<<endl;
    cout<<"排序之前的数据：";
    for(int i=0;i<10;i++)
        cout<<data[i]<<" ";
    cout<<endl;
    heap_sort(data,10);
    cout<<"排序之后的数据：";
    for(i=0;i<10;i++)
        cout<<data[i]<<" ";
    cout<<endl;
    return 0;
}

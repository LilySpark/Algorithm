#include <iostream>
using namespace std;
int data[10]={71,18,151,138,160 ,63 ,174, 169 ,79 ,78 };

//��ĳ���ڵ�Ϊ���ڵ���������е���������Ϊ�󶥶�
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

//���ѵĹ��̣�ͨ���Ե����ϵص���max_heapify����һ������data��1����n�����һ���󶥶ѣ�
//ֻ��Ҫ�Գ���Ҷ�ӽڵ�����Ľڵ���е���
void bulid_max_heap(int data[],int heapsize)
{��������������������������������������������������
    for(int i=heapsize/2-1;i>=0;i--)
         max_heapify(data,i,heapsize);
}

//�������㷨ʵ�����壺����bulid_max_heap���������鹹��ɴ󶥶ѣ�
//Ȼ��data��0���Ͷѵ����һ��Ԫ���������������е���
void heap_sort(int data[],int heapsize)
{����������������������������������������������
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
    cout<<"�������㷨ʵ��"<<endl;
    cout<<"����֮ǰ�����ݣ�";
    for(int i=0;i<10;i++)
        cout<<data[i]<<" ";
    cout<<endl;
    heap_sort(data,10);
    cout<<"����֮������ݣ�";
    for(i=0;i<10;i++)
        cout<<data[i]<<" ";
    cout<<endl;
    return 0;
}

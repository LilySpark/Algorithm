#include <iostream>

using namespace std;

void selectSort(int* a, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int min = a[i];
        int index = i;
        for(int j = i + 1; j < n; j++)
        {
            if(min > a[j]){
                min = a[j];
                index = j;
            }
        }
        swap(a[i], a[index]);
    }
}

void bubbleSort(int* a, int n)
{
    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-1-i; j++)
        {
            if(a[j] > a[j+1])
                swap(a[j],a[j+1]);
        }
    }
}

void insertSort(int* a, int n)
{
    for(int i = 1; i < n; i++)
    {
        if(a[i] < a[i-1])
        {
            int temp = a[i];
            int j;
            for(j = i-1; j >=0; j--)
            {
                if(a[j] > temp)
                    a[j+1] = a[j];
                else
                    break;
            }
            a[j+1] = temp;
        }
    }
}


int partition(int* a, int low, int high)
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

void QuickSort(int* a, int p, int r)
{
    if(p < r)
    {
        int q = partition(a,p,r);
        QuickSort(a, p, q-1);
        QuickSort(a, q+1, r);
    }
}


void mergeArray(int* a, int first, int mid, int last)
{
    int i = first;
    int j = mid + 1;
    int* temp = new int[last-first+1];
    int k = 0;
    while(i <= mid && j <= last)
    {
        if(a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while(i <= mid)
        temp[k++] = a[i++];

    while(j <= last)
        temp[k++] = a[j++];

    for(i=0; i < k; i++)
        a[first + i] = temp[i];
    delete[] temp;
}

void MergeSort(int* a, int first, int last)
{
    if(first < last)
    {
        int mid = (first + last)/2;
        MergeSort(a, first, mid);
        MergeSort(a, mid+1, last);
        mergeArray(a, first, mid, last);
    }
}



int main()
{
    int a[] = {4,2,8,5,10,7};
    insertSort(a,6);
    for(int i=0; i < 6; i++)
        cout<<a[i]<<" ";
    cout<<endl;

}

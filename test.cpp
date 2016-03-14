#include <iostream>

using namespace std;

int main()
{
    int* a = new int[10];

    for(int i = 0; i < 10; i++)
        a[i] = i+1;

    for(int i = 0; i < 10; i++)
        cout<<a[i]<<" ";
    cout<<endl;

    delete [] a;

    for(int i = 0; i < 10; i++)
        cout<<a[i]<<" ";

    int * b[2];
    b[0]= new int[3];
    b[1]=new int[3];
    delete b[0];
    delete b[1];


}

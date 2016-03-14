#include <iostream>
#include <cstring>

using namespace std;

char c[10][10] =
{
    "",
    "",
    "ABC",
    "DEF",
    "GHI",
    "JKL",
    "MNO",
    "PQRS",
    "TUV",
    "WXYZ",
};
const int n = 5;

int total[10] = {0,0,3,3,3,3,3,4,3,4};


void numToEnglish(int n, int* number,int* answer)
{
    int count = 0;
    //k表示电话号码的第k位
    while(true)
    {
        cout<<++count<<" : ";
        for(int i = 0; i < n; i++)
            cout<<c[number[i]][answer[i]];
        cout<<endl;
        int k = n-1;
        while(k >= 0)
        {
            if(answer[k] < total[number[k]] - 1)
            {
                answer[k]++;
                break;
            }
            else{
                answer[k] = 0;
                k--;
            }
        }
        if(k < 0)
            break;
    }

}


int count = 0;
void RecursiveSearch(int* number, int* answer, int index, int n)
{
    if(index == n)
    {
        cout<<++count<<" : ";
        for(int i = 0; i < n; i++)
            cout<<c[number[i]][answer[i]];
        cout<<endl;
        return;
    }
    for(answer[index] = 0; answer[index] < total[number[index]]; answer[index]++)
        RecursiveSearch(number, answer, index+1, n);
}

int main()
{
    int number[n] = {2,3,4,5,6};
    int* answer = new int[n];
    memset(answer,0,n*sizeof(int));

    //numToEnglish(n, number,answer);
    RecursiveSearch(number, answer, 0, n);

    delete[] answer;

}

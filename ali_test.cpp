#include <iostream>
#include <vector>
using namespace std;


void output(vector<int> a)
{
    for(int i = 0; i < a.size(); i++)
        cout<<a[i]<<",";
    cout<<endl;
}

void selectSort(vector<int>& a)
{
    int n = a.size();
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

void sort(vector<vector<int>> a)
{
    for(int i = 0; i < a.size(); i++)
        selectSort(a[i]);

    int j = 0;
    int num = 0;
    while(true)
    {
        vector<int> b;
         for(int i = 0; i < a.size(); i++)
         {
             if(j < a[i].size())
                b.push_back(a[i][j]);
              else
                num++;
         }
         selectSort(b);
         output(b);
         j++;
         if(num == a.size())
            break;
    }
}

int main()
{
    vector<vector<int>

}


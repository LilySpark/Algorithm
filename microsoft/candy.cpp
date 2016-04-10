#include <iostream>
#include <string>
#include <vector>

using namespace std;


void mysort(vector<double>& a, vector<int>& idx)
{
    int n = a.size();
    for(int i = 0; i < n-1; i++)
    {
        double max = a[i];
        int id = i;
        for(int j = i+1; j < n; j++)
        {
            if(a[j]>max)
            {
                max = a[j];
                id = j;
            }
        }
        swap(a[id],a[i]);
        idx.push_back(id);
       //cout<<max<<" ";
    }
}

int main(void)
{
    int n, v;
    while(cin >> n >> v)
    {
        int a;
        double b;
        vector<int> category;
        vector<double> values;
        vector<double> units;
        for(int i = 0; i < n; i++)
        {
            cin>>a>>b;
            category.push_back(a);
            values.push_back(b);
            units.push_back((double)b/a);
        }
        vector<int> idx;
        mysort(units,idx);

        int sum = 0;
        int weight = 0;
        int i = 0;
        vector<int> newidx;
        while(weight < v)
        {
            sum += values[idx[i]];
            weight += category[idx[i]];
            newidx.push_back(idx[i]);
            i++;
        }
        if(weight > v)
        {
            sum -= values[idx[i]];
            weight -= category[idx[i]];
            for(int j = i+1; j < n; j++)
            {
                if(category[idx[j]] == 1)
                    {
                        sum += values[idx[j]];
                        weight += category[idx[j]];
                        newidx[i-1] = idx[j];
                    }
            }
        }

        cout<<sum<<endl;
        int m = newidx.size();
        for(int j = 0; j < m; j++)
        {
            int min = newidx[j];
            int id = j;
            for(int k = j+1; k < m; k++)
            {
                if(newidx[k]<min)
                {
                    min = newidx[k];
                    id = k;
                }

            }
            swap(newidx[id],newidx[j]);
            if(j==0)
                cout<<min+1;
            else
                cout<<" "<<min+1;
        }

        cout<<endl;
    }
    return 0;
}

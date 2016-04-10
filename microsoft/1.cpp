#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main(void)
{
    int t;
    int n,p,w,h;
    cin>>t;
    while(t--)
    {
        int s=0;
        float sum = 0;
        cin>>n>>p>>w>>h;
        vector<float> a(n,0.0);
        for(int i = 0; i < n; i++){
            cin>>a[i];
            sum += a[i];
        }

        int pages = 0;
        while(pages < p)
        {
            s++;
            int perWidth = w/s;
            int perHeigh = h/s;
            float lines = 0.0;
            for(int i = 0; i < n; i++){
                lines += ceil(a[i]/perWidth);
            }
            pages = ceil(lines/perHeigh);
        }
        if(pages == p)
            cout<<s<<endl;
        else
            cout<<s-1<<endl;
    }


    return 0;
}

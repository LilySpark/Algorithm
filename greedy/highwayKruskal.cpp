#include <iostream>        //最小生成树Kruskal算法
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=520,maxm=125020;    //有效总边数是C(500,2)
int n,m;    //n,m分别是结点数和边数
int p[maxn];    //记录并查集中该结点的父亲
int u[maxm],v[maxm],w[maxm];        //保存边的端点序号和权值
int r[maxm];    //用于间接排序－－排序的关键字是对象的“代号”，而不是对象本身
int cmp(const int i,const int j)
{
    return w[i]<w[j];
}
int find(int x)
{
    return p[x]==x ? x : p[x]=find(p[x]);
}
int Kruskal()
{
    int i,e,x,y;
    for(i=0;i<n;++i)
        p[i]=i;
    for(i=0;i<m;++i)
        r[i]=i;
    sort(r,r+m,cmp);
    int cnt=0;
    for(i=0;i<m;++i)
    {
        e=r[i];
        x=find(u[e]);
        y=find(v[e]);
        if(x!=y)
        {
            p[x]=y;
            cnt++;
            if(cnt==n-1)
                return w[e];    //最小生成树的最大边
        }
    }
}
int main()
{
    int cases,wei;
    scanf("%d",&cases);
    while(cases--)
    {
        scanf("%d",&n);
        m=0;    //边数
        for(int i=0;i<n;++i)    //结点下标从0开始
        {
            for(int j=0;j<n;++j)
            {
                scanf("%d",&wei);
                if(j>i)
                {
                    u[m]=i;
                    v[m]=j;
                    w[m]=wei;
                    m++;
                }
            }
        }
        printf("%d\n",Kruskal());
        if(cases>0)
            printf("\n");
    }
    return 0;
}

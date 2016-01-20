// 题意:找出最小生成树的最大边
#include<iostream>            //最小生成树Prim算法
using namespace std;
struct MST    //最小生成树的边
{
    int st,ed,w;
}mst[1000];
int n,edge[1000][1000];
int ans;    //ans保存最小生成树的最长边
void Prim()
{
    int i,j,k;
    for(i=0;i<n-1;i++)    //默认选择节点0加入生成树
    {
        mst[i].st=0;mst[i].ed=i+1;
        mst[i].w=edge[0][i+1];
    }
    for(i=0;i<n-1;++i)        //求n-1条边
    {
        int min_w=100000;
        for(j=i;j<n-1;++j)
        {
            if(mst[j].w<min_w)        //求最小权值边
            {
                min_w=mst[j].w;
                k=j;
            }
        }
        swap(mst[k],mst[i]);    //最小边移至前端
        int v=mst[i].ed;
        ans=max(ans,mst[i].w);
        for(j=i+1;j<n-1;++j)    //更新后面的边
        {
            int wei=edge[v][mst[j].ed];
            if(wei<mst[j].w)
            {
                mst[j].w=wei;
                mst[j].st=v;
            }
        }
    }
}
int main()
{
    int cases;
    cin>>cases;
    while(cases--)
    {
        cin>>n;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                cin>>edge[i][j];
        ans=0;
        Prim();
        cout<<ans<<endl;
        if(cases>0)
            cout<<endl;
    }
    return 0;
}

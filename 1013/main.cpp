/*
#include <iostream>
#include<fstream>
using namespace std;
int N;
int g[1000][1000];
int vis[1000];
void dfs(int s){
    vis[s] =1;
    for(int i=0;i<N;i++)
    {
        if(g[s][i]==1&&!vis[i])
            dfs(i);
    }
}
int main()
{
    ifstream cin("1.txt");
    int m,k;
    cin>>N>>m>>k;

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            g[i][j]=0;
        }
    }
    while(m--)
    {
        int p,q;
        cin>>p>>q;
        g[p-1][q-1] =1;
        g[q-1][p-1] =1;
    }
    for(int i=0;i<k;i++)
    {

        int city;
        cin>>city;
        city = city-1;
        for(int j=0;j<N;j++)
        {
            vis[j]=0;
        }
        vis[city] = 1;
        int con_num = 0;
        for(int j=0;j<N;j++)
        {
            if(!vis[j])
            {
                dfs(j);
                con_num++;
            }
        }
        cout<<con_num-1<<endl;


    }
}

*/
//scanf在输入大量数据时效率高
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
vector<int> g[1000];
int N;
int vis[1000];
void dfs(int s)
{
    vis[s] =1;
    for(int i=0;i<g[s].size();i++)
    {
        if(!vis[g[s][i]])
            dfs(g[s][i]);
    }
}
int main()
{
    //ifstream cin("1.txt");
    freopen("1.txt","r",stdin);
    int m,k;
    scanf("%d%d%d", &N, &m, &k);
    while(m--)
    {
        int p,q;
        scanf("%d%d",&p,&q);
        g[p-1].push_back(q-1);
        g[q-1].push_back(p-1);
    }
    //cout<<g[0][0]<<endl;
    for(int i=0;i<k;i++)
    {
        int city;
        scanf("%d",&city);
        city=city-1;
        int con_num =0;

        //for(int j=0;j<N;j++)
        //{

            //for(int k=0;k<g[j].size();k++)
            //{
            //   if(j!=city&&g[j][k]!=city);
            //        g1[j].push_back(g[j][k]);
            //}
            //
          //  vis[j]=0;
        //}
        fill(vis, vis + 1000, 0);
        vis[city] = 1;
        for(int j=0;j<N;j++)
        {
            if(!vis[j])
            {
                dfs(j);
                con_num++;
            }
        }
        cout<<con_num-1<<endl;

    }
    return 0;

}



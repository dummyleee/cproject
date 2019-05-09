/*
#include <iostream>
#include<vector>
#include<fstream>
#define max_v 500
#define INFTY 99999
using namespace std;
struct edge{
    int to;
    int cost;
};
vector<edge> g[max_v];
int team[max_v];
int C;
int N;
void print(int pre[],int s){
    if(pre[s]!=-1)
        print(pre, pre[s]);
    cout<<s<<"->";
}
void dijkstra(int t)
{
    int pre[N+1];
    int vis[N+1];
    int dis[N+1];
    int num[N+1];
    for(int i =0;i<=N;i++)
    {
        vis[i] = 0;
        dis[i] = INFTY;
        num[i] = 0;
    }
    dis[0] = 0;
    pre[0] = -1;
    while(!vis[t])
    {
        int min_d = INFTY;
        int u;
        for(int i=0;i<=N;i++)
        {
            if(!vis[i]&&min_d>dis[i])
            {
                min_d = dis[i];
                u = i;
            }
        }
        vis[u] = 1;
        for(int i=0;i<g[u].size();i++)
        {
            if(!vis[g[u][i].to]&&dis[g[u][i].to]>=dis[u]+g[u][i].cost)
            {
                if(dis[g[u][i].to]>dis[u]+g[u][i].cost)
                {
                    dis[g[u][i].to]=dis[u]+g[u][i].cost;
                    num[g[u][i].to] = num[u]+team[g[u][i].to];
                    pre[g[u][i].to] = u;
                }
                else
                {
                    if(abs(num[g[u][i].to])>abs(num[u]+team[g[u][i].to]))
                    {
                        num[g[u][i].to] = num[u]+team[g[u][i].to];
                        pre[g[u][i].to] = u;
                    }
                }
            }
        }
    }
    if(num[t]<0)
        cout<<abs(num[t])<<' ';
    else
        cout<<'0'<<' ';
    print(pre, pre[t]);
    cout<<t<<' ';
    if(num[t]>0)
        cout<<abs(num[t]);
    else
        cout<<'0';

}
int main()
{
    ifstream cin("1.txt");
    int t, m;
    cin>>C>>N>>t>>m;
    int a;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        team[i] = a-C/2;
    }
    team[0]=0;
    while(m--)
    {
        int p,q,c;
        cin>>p>>q>>c;
        edge e1,e2;
        e1.to = p;e1.cost=c;
        e2.to = q;e2.cost=c;
        g[p].push_back(e2);
        g[q].push_back(e1);
    }
    dijkstra(t);
}
*/
#include <iostream>
#include<vector>
#include<fstream>
#define max_v 510
#define INFTY 99999
using namespace std;
struct edge{
    int to;
    int cost;
};
vector<edge> g[max_v];
int team[max_v];
int C;
int N;
int vis[max_v];
int dis[max_v];
vector<int> pre[max_v];
void dijkstra(int s)
{
    for(int i=1;i<=N;i++)
    {
        vis[i] = 0;
        dis[i] = INFTY;
    }
    dis[0] =0;
    while(!vis[s])
    {
        int min_d =INFTY;
        int u=-1;
        for(int i=0;i<=N;i++)
        {
            if(!vis[i]&&min_d>dis[i])
            {
                min_d =dis[i];
                u = i;
            }
        }
        if(u==-1)break;
        vis[u] =1;
        for(int i=0;i<g[u].size();i++)
        {
            int j = g[u][i].to;
            if(!vis[j]&&dis[j]==dis[u]+g[u][i].cost)
            {
                pre[j].push_back(u);
            }
            if(!vis[j]&&dis[j]>dis[u]+g[u][i].cost)
            {
                dis[j] = dis[u]+g[u][i].cost;
                pre[j].clear();
                pre[j].push_back(u);
            }
        }
    }
}
vector<int> path,temppath;
int min_back =INFTY,min_need =INFTY;
 void dfs(int t)
 {
    temppath.push_back(t);
    if(t==0)
    {
        int bk=0,nd=0;
        for(int i=temppath.size()-1;i>=0;i--)
        {
            int cur = temppath[i];
            if(team[cur]>=0)
            {
                bk +=team[cur];
            }else if(bk>=(-team[cur]))
            {
                bk +=team[cur];
            }else{
                nd =nd+abs(team[cur])-bk;
                bk=0;
            }
        }
        if(min_need>nd)
        {
            path = temppath;
            min_need = nd;
            min_back = bk;
        }
        else if(min_need==nd)
        {
            if(min_back>bk)
            {
                path = temppath;
                min_back = bk;
            }
        }
        temppath.pop_back();
        return ;
    }
    for(int i=0;i<pre[t].size();i++)
    {
        dfs(pre[t][i]);
    }
    temppath.pop_back();
 }
int main()
{
    ifstream cin("1.txt");
    int t, m;
    cin>>C>>N>>t>>m;
    int a;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        team[i] = a-C/2;
    }
    team[0]=0;
   // cout<<team[1]<<team[3]<<endl;
    while(m--)
    {
        int p,q,c;
        cin>>p>>q>>c;
        edge e1,e2;
        e1.to = p;e1.cost=c;
        e2.to = q;e2.cost=c;
        g[p].push_back(e2);
        g[q].push_back(e1);
    }
    dijkstra(t);
    dfs(t);
    cout<<min_need<<' ';
    for(int i=path.size()-1;i>=1;i--)
    {
        cout<<path[i]<<"->";
    }
    cout<<t<<' '<<min_back;
}

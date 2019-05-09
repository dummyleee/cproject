#include <iostream>
#include<vector>
#include<fstream>
#define max_v 500
#define INF 9999999
using namespace std;
struct edge
{
    int to;
    int cost;
    int diss;
};
int N;
vector<edge> g[max_v];
int dis[max_v];
int vis[max_v];
int min_cost[max_v];
int pre[max_v];
void print(int s)
{
    if(pre[s]!=-1)
    {
        print(pre[s]);
    }
    cout<<s<<' ';
}
void dijkstra(int s, int t)
{
    for(int i=0;i<N;i++)
    {
        dis[i] = INF;
        vis[i] = 0;
        min_cost[i] =INF;
    }
    min_cost[s] = 0;
    dis[s] = 0;
    pre[s] =-1;
    while(!vis[t])
    {
        int min_d=INF;
        int u;
        for(int i=0;i<N;i++)
        {
            if(!vis[i]&&min_d>dis[i])
            {
                min_d = dis[i];
                u=i;
            }
        }
        vis[u] = 1;
        for(int i=0;i<g[u].size();i++)
        {
            int j = g[u][i].to;
            if(!vis[j]&&dis[j]>=dis[u]+g[u][i].diss)
            {
                if(dis[j]==dis[u]+g[u][i].diss)
                {
                    if(min_cost[j]>min_cost[u]+g[u][i].cost)
                    {
                        min_cost[j] = min_cost[u]+g[u][i].cost;
                        pre[j] = u;
                    }
                }
                else{
                    dis[j]=dis[u]+g[u][i].diss;
                    min_cost[j] = min_cost[u] +g[u][i].cost;
                    pre[j] =u;
                }
            }
        }

    }
    print(t);
    cout<<dis[t]<<' '<<min_cost[t];

}
int main()
{
    ifstream cin("1.txt");
    int m,s,t;
    cin>>N>>m>>s>>t;
    while(m--)
    {
        int p,q,d,c;
        cin>>p>>q>>d>>c;
        edge e1,e2;
        e1.to=p;
        e2.to=q;
        e1.cost=e2.cost=c;
        e1.diss=e2.diss=d;
        g[p].push_back(e2);
        g[q].push_back(e1);
    }
    dijkstra(s,t);
}

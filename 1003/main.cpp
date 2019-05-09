/*
#include <iostream>
#include<fstream>
#define INFTY 99999
using namespace std;
const int max_city = 500;
int city[max_city][max_city];
void dijkstra(int s,int t,int n,int team[])
{
    int num[n];
    int amount[n];
    int vis[n];
    int dis[n];
    for(int i=0;i<n;i++)
    {
        dis[i] = INFTY;
        vis[i] = 0;
        num[i] = 0;
        amount[i] =0;
    }
    dis[s] = 0;
    amount[s] = team[s];
    num[s] = 1;
    while(!vis[t])
    {
        int min_d = INFTY;
        int u;
        for(int i=0;i<n;i++)
        {
            if(!vis[i]&&dis[i]<min_d)
            {
                min_d=dis[i];
                u = i;
            }
        }
        vis[u] = 1;
        for(int i =0;i<n;i++){
            if(!vis[i]&&dis[i]>=dis[u]+city[u][i])
            {

                if(dis[i]==dis[u]+city[u][i])
                {
                    num[i]=num[i]+num[u];
                    if(amount[i]<amount[u]+team[i])
                        amount[i] = amount[u]+team[i];
                }
                else
                {
                    num[i] = num[u];
                    amount[i] = amount[u] + team[i];
                }
                dis[i]=dis[u]+city[u][i];

            }
        }

    }
    cout<<num[t]<<' '<<amount[t];

}
int main()
{
    ifstream cin("1.txt");
    int n,m,s,t;
    cin>>n>>m>>s>>t;
    int team[n];
    for(int i=0;i<n;i++)
    {
        cin>>team[i];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            city[i][j]=INFTY;
        }
    }
    for(int i=0;i<m;i++)
    {
        int p,q,l;
        cin>>p>>q>>l;
        city[p][q]=l;
        city[q][p]=l;
    }
    dijkstra(s,t,n,team);
}
*/
#include<iostream>
#include<fstream>
#include<vector>
#define max_v 500
#define INFTY 999999
using namespace std;
struct edge
{
    int to;
    int cost;
};
vector<edge> G[max_v];
int team[max_v];

void dijkstra(int s,int t,int n)
{
    int dis[n];
    int vis[n];
    int num[n];
    int amount[n];
    for(int i=0;i<n;i++)
    {
        dis[i]=INFTY;
        vis[i]=0;
        num[i]=0;
        amount[i]=0;
    }
    dis[s] = 0;
    num[s] = 1;
    amount[s] = team[s];
    while(!vis[t])
    {
        int min_d = INFTY;
        int u;
        for(int i=0;i<n;i++)
        {
            if(!vis[i]&&dis[i]<min_d)
            {
                min_d = dis[i];
                u = i;
            }
        }
        vis[u] = 1;
        for(int i=0;i<G[u].size();i++)
        {
            int j=G[u][i].to;
            if(!vis[j]&&dis[j]>=dis[u]+G[u][i].cost)
            {
                if(dis[j]==dis[u]+G[u][i].cost)
                {
                    num[j] = num[u]+num[j];
                    if(amount[j]<amount[u]+team[j])
                        amount[j]=amount[u]+team[j];
                }
                else
                {
                    num[j] = num[u];
                    amount[j] = amount[u]+team[j];
                }
                dis[j] = dis[u]+G[u][i].cost;
            }
        }
    }
    cout<<num[t]<<' '<<amount[t];
}
int main(){
    ifstream cin("1.txt");
    int n,m,s,t;
    cin>>n>>m>>s>>t;
    for(int i=0;i<n;i++){
        cin>>team[i];
    }
    while(m--){
        int p,q,c;
        cin>>p>>q>>c;
        edge e1,e2;
        e1.to=p;
        e1.cost=c;
        e2.to =q;
        e2.cost =c;
        G[p].push_back(e2);
        G[q].push_back(e1);

    }
    dijkstra(s, t, n);
    return 0;
}



























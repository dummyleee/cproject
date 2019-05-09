#include <iostream>
#include<vector>
#include<fstream>
#include<iomanip>
#define max_v 1100
#define INF 99999
using namespace std;
struct edge{
    int to;
    int cost;
};
vector<edge> g[max_v];
int N,M;
int vis[max_v];
int dis[11][max_v];
double max_dis,min_dis,ave_dis;
void  dijkstra(int s)
{
    int t=s-N;

    for(int i=1;i<=N+M;i++)
    {
        vis[i] = 0;
        dis[t][i] = INF;
    }
    dis[t][s] = 0;

    for(int i=1;i<=N+M;i++)
    {
        int min_d = INF;
        int u;
        for(int j=1;j<=N+M;j++)
        {
            if(!vis[j]&&min_d>dis[t][j])
            {
                min_d = dis[t][j];
                u=j;
            }
        }
        //cout<<u<<endl;
        vis[u]=1;
        if(u<=N&&max_dis<dis[t][u])
        {
            max_dis = dis[t][u];
        }
        if(u<=N&&min_dis>dis[t][u])
            min_dis = dis[t][u];
        if(u<=N)
            ave_dis += dis[t][u];
        for(int j=0;j<g[u].size();j++)
        {
            int k=g[u][j].to;
            if(!vis[k]&&dis[t][k]>dis[t][u]+g[u][j].cost)
                dis[t][k] = dis[t][u]+g[u][j].cost;
        }
    }
    //return max_dis;
}
int main()
{
    ifstream cin("1.txt");
   int k,d;
   cin>>N>>M>>k>>d;
    while(k--)
    {
        string a,b;
        int c;
        int v1,v2;
        cin>>a>>b>>c;
        if(a.length()==1)
            v1= a[0] -'0';
        else
        {
            v1=a[1] -'0'+N;
        }
        if(b.length()==1)
            v2= b[0] -'0';
        else
        {
            v2=b[1] -'0'+N;
        }
        edge e1,e2;
        e1.to = v1;
        e2.to = v2;
        e1.cost=e2.cost =c;
        g[v1].push_back(e2);
        g[v2].push_back(e1);
    }
    double last_min=-1;
    double last_ave = 0;
    int choose =0;
    for(int i=1;i<=M;i++)
    {
        max_dis = 0;
        min_dis =INF;
        ave_dis =0;
        //cout<<"1"<<endl;
        dijkstra(i+N);
        //cout<<"1"<<endl;
        //cout<<temp<<endl;
        if(max_dis<=d)
        {
            if(last_min==min_dis)
            {
                if(last_ave>ave_dis)
                {
                    last_ave  = ave_dis;
                    choose = i;
                }
            }
            else if(last_min<min_dis)
            {
                last_min = min_dis;
                last_ave = ave_dis;
                choose = i;
            }
        }
    }
    if(!choose)
    {
        cout<<"No Solution";
        return 0;
    }
    cout<<'G'<<choose<<endl;
    cout<<setiosflags(ios::fixed)<<setprecision(1)<<last_min<<' '<<int((last_ave/N+0.05)*10)/10.0;
    //cout<<setw(10)<<setfill('0')<<"0"<<endl;
    return 0;
}

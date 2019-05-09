/*
#include <iostream>
#include<map>
#include<fstream>
#define INF 9999
#define max_v 201
using namespace std;
int N;
string name[max_v];
map<string, int> m1;
int value[max_v];
int g[max_v][max_v];
int vis[max_v];
int dis[max_v];
int happy[max_v];
int total_city[max_v];
int pre[max_v];
int num_of_least[max_v];
void print(int t)
{
    if(t==1)
        return;
    print(pre[t]);
    cout<<"->"<<name[t];
}

void dijkstra(int s,int t)
{
    for(int i=1;i<=N;i++)
    {
        dis[i] = INF;
        vis[i] = 0;
        happy[i] = 0;
        total_city[i] = 0;
        num_of_least[i] =0;
    }
    dis[s] = 0;
    happy[s] =value[s];
    total_city[s] = 0;
    pre[s] =-1;
    num_of_least[s] =1;
    while(!vis[t])
    {
        int u;
        int min_d =INF;
        for(int i=1;i<=N;i++)
        {
            if(!vis[i]&&min_d>dis[i])
            {
                min_d = dis[i];
                u = i;
            }
        }
        vis[u] =1;
        for(int i=1;i<=N;i++)
        {
            if(!vis[i]&&g[u][i]>0)
            {
                if(dis[i]==dis[u]+g[u][i])
                {
                    if(happy[i]==happy[u]+value[i])
                    {
                        if(total_city[i]>total_city[u]+1)
                        {
                            pre[i] = u;
                            total_city[i]=total_city[u]+1;
                        }
                    }
                    else if(happy[i]<happy[u]+value[i])
                    {
                        happy[i] = happy[u]+value[i];
                        pre[i] = u;
                        total_city[i] = total_city[u]+1;
                    }
                    num_of_least[i] = num_of_least[i]+num_of_least[u];
                }
                else if(dis[i]>dis[u]+g[u][i])
                {
                    dis[i] = dis[u]+g[u][i];
                    pre[i] = u;
                    happy[i] = happy[u]+value[i];
                    total_city[i] = total_city[u]+1;
                    num_of_least[i] = num_of_least[u];
                }
            }
        }
    }
    cout<<pre[m1["ROM"]]<<endl;
    cout<<num_of_least[t]<<' '<<dis[t]<<' '<<happy[t]<<' '<<happy[t]/total_city[t]<<endl;
    cout<<"HZH";
    print(t);
}
int main()
{
    ifstream cin("1.txt");
    int k;
    string source;
    cin>>N>>k>>source;
    name[1] = source;
    value[1] = 0;
    m1[source] = 1;
    for(int i=2;i<=N;i++)
    {
        string city;
        int v;
        cin>>city>>v;
        name[i] = city;
        value[i] = v;
        m1[city] = i;
    }

    while(k--)
    {
        string s1,s2;
        int cost;
        cin>>s1>>s2>>cost;
        g[m1[s1]][m1[s2]] = cost;
        g[m1[s2]][m1[s1]] = cost;
    }
    dijkstra(1, m1["ROM"]);
}
*/
//这道题是我见过的最坑的题，给的样例中应该有两个城市距离为0，这样输出居然还对了

#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#define INF 999999999
#define max_v 201
using namespace std;
string name[max_v];
map<string, int> m1;
int value[max_v];
int g[max_v][max_v];
int N;
int vis[max_v];
int dis[max_v];
vector<int> pre[max_v];

void dijkstra(int s,int t)
{
    for(int i=1;i<=N;i++)
    {
        dis[i] =INF;
        vis[i] =0;
    }
    dis[s] = 0;
    while(!vis[t])
    {
        int min_d =INF;
        int u;
        for(int i=1;i<=N;i++)
        {
            if(!vis[i]&&min_d>dis[i])
            {
                min_d = dis[i];
                u = i;
            }
        }
        vis[u] =1;
        for(int i=1;i<=N;i++)
        {
            if(!vis[i]&&g[u][i]!=INF)
            {
                if(dis[i]==dis[u]+g[u][i])
                {
                    pre[i].push_back(u);
                }
                else if(dis[i]>dis[u]+g[u][i])
                {
                    pre[i].clear();
                    dis[i] = dis[u]+g[u][i];
                    pre[i].push_back(u);
                }
            }
        }
    }
}
vector<int> temppath,path;
int max_happy=0;
double max_ave=0;
int cnt=0;
void dfs(int s)
{
    temppath.push_back(s);
    if(s==1)
    {
        int temp = 0;
        for(int i=0;i<temppath.size();i++)
            temp += value[temppath[i]];
        int temp_ave = 1.0*temp/(temppath.size()-1);
        if(temp>max_happy)
        {
            max_happy = temp;
            path = temppath;
            max_ave = temp_ave;
        }
        else if(max_happy==temp)
        {
            if(temp_ave>max_ave)
            {
                max_ave = temp_ave;
                path = temppath;
            }
        }
        temppath.pop_back();
        cnt++;
        return;
    }
    for(int i=0;i<pre[s].size();i++)
    {
        dfs(pre[s][i]);
    }
    temppath.pop_back();
}
int main()
{
    fill(g[0],g[0]+max_v*max_v, INF);
    ifstream cin("1.txt");
    int k;
    string source;
    cin>>N>>k>>source;
    name[1] = source;
    value[1] = 0;
    m1[source] = 1;
    for(int i=2;i<=N;i++)
    {
        string city;
        int v;
        cin>>city>>v;
        name[i] = city;
        value[i] = v;
        m1[city] = i;
    }
    while(k--)
    {
        string s1,s2;
        int cost;
        cin>>s1>>s2>>cost;
        g[m1[s1]][m1[s2]] = cost;
        g[m1[s2]][m1[s1]] = cost;
    }
    int t = m1["ROM"];
    dijkstra(1, t);
    dfs(m1["ROM"]);
    cout<<cnt<<' '<<dis[t]<<' '<<max_happy<<' '<<int(max_ave)<<endl;
    cout<<name[1];
    for(int i=path.size()-2;i>=0;i--)
        cout<<"->"<<name[path[i]];
    return 0;
}

#include <iostream>
#include<vector>
#include<set>
#include<fstream>
#define max_v 10001
using namespace std;
int N;
vector<int> g[max_v];
set<int> res;
int vis[max_v];
int max_height = 0;
int height_node[max_v];
void dfs(int s,int height)
{
    if(height>max_height)
        max_height=height;
    vis[s]=1;
    int flag =0;
    for(int j=0;j<g[s].size();j++)
    {
        if(!vis[g[s][j]])
        {
            flag =1;
            dfs(g[s][j],height+1);
        }
    }
    height_node[s] = height;
}
int main()
{
    ifstream cin("1.txt");
    cin>>N;
    int p,q;
    for(int i=0;i<N-1;i++)
    {
        //scanf("%d%d",&p,&q);
        cin>>p>>q;
        g[p].push_back(q);
        g[q].push_back(p);
    }
    fill(vis, vis + max_v, 0);

    int con_num = 0;
    for(int i=1;i<=N;i++)
    {
        if(!vis[i])
        {
            dfs(i, 0);
            con_num++;
        }
    }
    if(con_num>1)
    {
        cout<<"Error: "<<con_num<<" components"<<endl;
        return 0;
    }
    for(int i=1;i<=N;i++)
    {
        if(height_node[i]==max_height)
            res.insert(i);
    }
    max_height =0;
    fill(vis, vis + max_v, 0);
    for(auto it=res.begin();it!=res.end();it++)
    {
        dfs(*it, 0);
        break;
    }
    for(int i=1;i<=N;i++)
    {
        if(height_node[i]==max_height)
            res.insert(i);
    }
    for(auto it=res.begin();it!=res.end();it++)
    {
        cout<<*it<<endl;
    }
    return 0;
}



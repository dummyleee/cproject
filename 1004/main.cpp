/*
#include <iostream>
#include<fstream>
#include<vector>
#include<queue>
#define max_v 100
using namespace std;
int N;
int num[max_v];
int max_height;
int vis[max_v];
vector<int> tree[max_v];
void dfs(int s,int height)
{
    if(height>max_height)
    {
        max_height =height;
    }
    vis[s] = 1;
    int flag=0;
    for(int i=0;i<tree[s].size();i++)
    {
        if(!vis[tree[s][i]])
        {
            dfs(tree[s][i], height+1);
            flag = 1;
        }
    }
    if(!flag)
    {
        num[height]+=1;
    }

}

int main()
{
    fstream cin("1.txt");
    int m;
    cin>>N>>m;
    max_height = 0;
    for(int i=1;i<=N;i++)
    {
        num[i] = 0;
    }
    while(m--)
    {
        int id, k;
        cin>>id>>k;
        while(k--)
        {
            int child;
            cin>>child;
            tree[id].push_back(child);
        }
    }
    dfs(1,1);
    cout<<num[1];
    for(int i=2;i<=max_height;i++)
    {
        cout<<' '<<num[i];
    }
    return 0;
}
*/
#include <iostream>
#include<fstream>
#include<vector>
#include<queue>
#define max_v 100
using namespace std;
int N;
int num[max_v];
int max_height;
int vis[max_v];
vector<int> tree[max_v];
int level[max_v];
void bfs(int s)
{
    queue<int> q;
    q.push(s);
    vis[s]  =1;
    max_height = 1;
    level[s] =1;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        int flag =0;
        for(int i=0;i<tree[cur].size();i++)
        {
            if(!vis[tree[cur][i]])
            {
                q.push(tree[cur][i]);
                level[tree[cur][i]] = level[cur]+1;
                if(max_height<level[cur]+1)
                    max_height = level[cur]+1;
                vis[tree[cur][i]] = 1;
                flag =1;
            }

        }
        if(!flag)
        {
            num[level[cur]]+=1;
        }

    }
    cout<<num[1];
    for(int i=2;i<=max_height;i++)
        cout<<' '<<num[i];
}
int main()
{
    fstream cin("1.txt");
    int m;
    cin>>N>>m;
    max_height = 0;
    for(int i=1;i<=N;i++)
    {
        num[i] = 0;
    }
    while(m--)
    {
        int id, k;
        cin>>id>>k;
        while(k--)
        {
            int child;
            cin>>child;
            tree[id].push_back(child);
        }
    }
    bfs(1);

}

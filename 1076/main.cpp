#include <iostream>
#include<fstream>
#include<vector>
#include<queue>
#define max_v 1010

using namespace std;
int g[max_v][max_v];
int N,L;
int vis[max_v];
int level[max_v];
int max_level;
int max_num;
void bfs(int s)
{
    queue<int> q;
    q.push(s);
    level[s] = 0;
    vis[s]=1;
    while(!q.empty())
    {
        int cur = q.front();
       // cout<<cur<<endl;
        q.pop();
        if(max_level<level[cur])
            max_level = level[cur];
        if(max_level>L)
            break;
        max_num++;
        for(int i=1;i<=N;i++)
        {
            if(!vis[i]&&g[cur][i]>0)
            {
                q.push(i);
                level[i] = level[cur]+1;
                vis[i] = 1;

            }
        }
    }
}
int main()
{
    ifstream cin("1.txt");
    cin>>N>>L;
    for(int i=1;i<=N;i++)
    {
        int k;
        cin>>k;
        while(k--)
        {
            int j;
            cin>>j;
            g[j][i] =1;
        }
    }
    //cout<<g[1][4]<<endl;
    int num;
    cin>>num;
    while(num--)
    {
        fill(vis, vis+max_v,0);
        fill(level, level+max_v, 2000);
        int id;
        cin>>id;
       // cout<<id<<endl;
       max_num=0;
       max_level = 0;
        bfs(id);

        cout<<--max_num<<endl;
    }
    return 0;
}

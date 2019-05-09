#include <iostream>
#include<vector>
#include<fstream>
#include<map>
#define max_v 2000
using namespace std;
int N;
map<string, int> m;
map<string, int> res;
int g[max_v][max_v]={0};
int t[max_v]={0};
int vis[max_v]={0};
int max_num;
int max_id, max_ctime, cluter_num, total_time;
int h[max_v];
void dfs(int s,int height)
{
    h[s] = height;
    cluter_num++;
    if(t[s]>max_ctime)
    {
        max_ctime=t[s];
        max_id = s;
    }
    vis[s] = 1;
    for(int i=0;i<max_num;i++)
    {
        if(vis[i]==0&&g[s][i]>0)
        {
            total_time+=g[s][i];
            dfs(i, height+1);
        }
        if(vis[i]==1&&g[s][i]>0&&height>h[i]+1)
            total_time+=g[s][i];
    }
}
int main()
{
    ifstream cin("1.txt");
    int m1,k;
    cin>>m1>>k;
    max_num = 0;
    while(m1--)
    {
        string a,b;
        int num1,num2;
        int time;
        cin>>a>>b>>time;
        if(m.find(a)!=m.end())
            num1 = m[a];
        else
        {
            num1 = max_num;
            m[a] = max_num;
            max_num++;
        }
        if(m.find(b)!=m.end())
            num2 = m[b];
        else{
            m[b] = max_num;
            num2 = max_num;
            max_num++;
        }
        g[num1][num2] +=time;
        g[num2][num1] +=time;
        t[num1]+=time;
        t[num2]+=time;
    }
    for(int i=0;i<max_num;i++)
    {
        if(vis[i]==0)
        {
            max_ctime = 0;
            cluter_num = 0;
            total_time = 0;
            dfs(i, 0);
            if(total_time>k&&cluter_num>2)
            {
                for(auto it=m.begin();it!=m.end();it++)
                {
                    if(it->second==max_id)
                    {
                        res[it->first] = cluter_num;
                        break;
                    }
                }
            }
        }
    }
    if(res.empty())
        cout<<'0'<<endl;
    else
    {
        cout<<res.size()<<endl;
        for(auto it=res.begin();it!=res.end();it++)
            cout<<it->first<<' '<<it->second<<endl;
    }
    return 0;
}

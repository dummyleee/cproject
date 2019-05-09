/*
#include <iostream>
#include<vector>
#include<map>
#include<queue>
#include<fstream>
#define max_v 10001
using namespace std;

map<int, string> m1;
map<string,int> m2;
int max_num =1;
int g[max_v][max_v];
vector<int> pre[max_v];
void bfs(int s,int t)
{
    int vis[max_num]={0};
    queue q;
    q.push(s);
    while(!q.empty()||!vis[t])
    {
        int cur =q.front();
        vis[cur] = 1;
        q.pop();
        for(int i=1;i<max_num;i++)
        {
            if(!vis[i]&&g[cur][i]>0)
            {
                pre[i].push_back(cur);
                q.push(i);
            }
        }
    }
}
vector<int> path,temppath;

void dfs(int s)
{

}
void find_road(string s,string t)
{
    //fill(pre,pre+max_num,0);
    for(int i=1;i<max_num;i++)
    {
        pre[i].clear();
    }
    bfs(m2[s],m2[t]);

}
int main()
{
    int line_num;
    cin>>line_num;

    for(int i=1;i<=line_num;i++)
    {
        int m;
        cin>>m;
        int last_num=0;
        while(m--)
        {
            string id;
            cin>>id;
            if(m2.find(id)!=m2.end())
            {
                line_id[m2[id]].push_back(i);
                if(last_num!=0)
                {
                    g[last_num][m2[id]] =g[m2[id]][last_num] = 1;
                }
            }
            else{
                line_id[max_num].push_back(i);
                m1[max_num] = id;
                m2[id] = max_num;
                if(last_num!=0)
                    g[last_num][m2[id]] =g[m2[id]][last_num] = 1;
                max_num++;

            }
        }
    }
    int k;
    cin>>k;
    while(k--)
    {
        string start,des;
        cin>>start>>des;
        find_road(start,des);
    }


}
*/
//³¬Ê±!!!!!!
#include<iostream>
#include<queue>
#include<vector>
#include<fstream>
#include<iomanip>
#define INF 99999
using namespace std;
int subway[10000][10000];
vector<int> temppath,path;
int min_stop=INF;
int min_line=INF;
int vis[10000];
void dfs(int s,int t)
{
    temppath.push_back(s);
    vis[s] =1;
    if(s==t)
    {
        int transfers =0;
        int last_line = 0;
        for(int i=0;i<temppath.size()-1;i++)
        {
            int stop1 = temppath[i];
            int stop2 = temppath[i+1];
            int cur_line = subway[stop1][stop2];
            if(last_line==0)
            {
                last_line = cur_line;
                continue;
            }
            if(last_line!=cur_line)
            {
                last_line=cur_line;
                transfers++;
            }
        }
        if(temppath.size()<min_stop)
        {
            min_line = transfers;
            min_stop = temppath.size();
            path = temppath;
        }
        if(temppath.size()==min_stop)
        {
            if(transfers<min_line)
            {
                min_line = transfers;
                path = temppath;
            }
        }
    }
    else
    {
        for(int i=0;i<10000;i++)
        {
            if(!vis[i]&&subway[s][i]>0)
                dfs(i,t);
        }
    }
    temppath.pop_back();
    vis[s] =0;
}
int main()
{
    ifstream cin("1.txt");
    int line_num;
    cin>>line_num;
    for(int i=1;i<=line_num;i++)
    {
        int k;
        cin>>k;
        int last_stop=-1;
        while(k--)
        {
            int stop;
            cin>>stop;
            if(last_stop==-1)
                last_stop=stop;
            else
            {
                subway[stop][last_stop]=i;
                subway[last_stop][stop]=i;
                last_stop = stop;
                }
        }
    }
    int n;
    cin>>n;
    //cout<<n;
    while(n--)
    {
        min_line =INF;
        min_stop = INF;
        fill(vis,vis+10000,0);
        int s,t;
        cin>>s>>t;
        dfs(s,t);
       // cout<<"1"<<endl;
        cout<<min_stop-1<<endl;
        int last_line =0;
        int start;
        int end_stop;
        for(int i=0;i<path.size()-1;i++)
        {
            int stop1 =path[i];
            int stop2 = path[i+1];
            int cur_line = subway[stop1][stop2];
            if(last_line==0)
            {
                start = stop1;
                end_stop = stop2;
                last_line = subway[stop1][stop2];
            }
            else if(last_line==cur_line)
            {
                end_stop = stop2;
            }else if(last_line!=cur_line)
            {
                cout<<"Take Line#"<<last_line<<' '<<"from "<<setw(4)<<setfill('0')<<start<<" to "<<setw(4)<<setfill('0')<<end_stop<<'.'<<endl;
                start = stop1;
                end_stop = stop2;
                last_line = cur_line;
            }
        }
        cout<<"Take Line#"<<last_line<<' '<<"from "<<setw(4)<<setfill('0')<<start<<" to "<<setw(4)<<setfill('0')<<end_stop<<'.'<<endl;
        //cout<<"Take Line#"<<last_line<<' '<<"from "<<start<<" to "<<end_stop<<'.'<<endl;
    }
    return 0;
}

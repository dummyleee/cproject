#include <iostream>
#include <string.h>
#include<queue>
#include<stdio.h>
#define max_n 257
using namespace std;
int cnt;
char s[max_n];
const int root=1;
int lch[max_n];
int rch[max_n];
int has_value[max_n];
int value[max_n];
void newtree()
{
    cnt = root;
    lch[root] =0;
    rch[root]=0;
    has_value[root]=0;
}
int newnode()
{
   int u=++cnt;
   lch[u]=rch[u]=has_value[u]=0;
   return u;
}
void addnode(int v, char* s){
    int n= strlen(s);
    int u=root;
    for(int i=0;i<n;i++)
    {
        if(s[i]=='L')
        {
            if(lch[u]==0)
                lch[u]=newnode();
            u=lch[u];
        }else if(s[i]=='R')
        {
            if(rch[u]==0)
                rch[u]=newnode();
            u=rch[u];
        }
    }
    if(!has_value[u])
    {
        value[u] = v;
        has_value[u] = 1;
    }
}
vector<int> ans;
bool bfs()
{
    queue<int> q;
    q.push(root);
    while(!q.empty())
    {
        int cur=q.front();
        q.pop();
        if(!has_value[cur])
            return false;
        ans.push_back(value[cur]);
        if(lch[cur]) q.push(lch[cur]);
        if(rch[cur])q.push(rch[cur]);
    }
    return true;
}
int main()
{
    freopen("1.txt","r",stdin);
    newtree();
    while(scanf("%s",s)==1)
    {
      //  printf("%s",s);
        if(!strcmp(s,"()"))
        {
            if(!bfs()){
                cout<<"-1"<<endl;
            }
            else
            {
                int len = ans.size();
                for(int i=0;i<len;i++)
                {
                    if(i==len-1)
                        cout<<ans[i]<<endl;
                    else
                        cout<<ans[i]<<' ';
                }
            }
            newtree();
           // continue;
        }
        else
        {
            int v;
            sscanf(&s[1],"%d",&v);
            addnode(v,strchr(s,',')+1);
        }

    }
    return 0;
}

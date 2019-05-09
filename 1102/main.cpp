#include <iostream>
#include<fstream>
#include<vector>
#include<set>
#include<queue>
#include<string.h>
using namespace std;
int lch[10],rch[10];
int level_order[10],in_order[10];
int N;
void bfs(int s)
{
    queue<int> q;
    q.push(s);
    int cnt=0;

    while(!q.empty())
    {
        int cur=q.front();
        q.pop();
        level_order[cnt++]=cur;
        if(lch[cur]!=-1)
            q.push(lch[cur]);
        if(rch[cur]!=-1)
            q.push(rch[cur]);
    }
}
int ct=0;
void dfs(int s)
{
    if(lch[s]!=-1)
            dfs(lch[s]);
    in_order[ct++]=s;
    if(rch[s]!=-1)
            dfs(rch[s]);
}
int main()
{
    freopen("1.txt","r",stdin);
    scanf("%d",&N);
    //cout<<N;
    set<int> st;
    for(int i=0;i<N;i++)
    {
        char s1[2],s2[2];
        scanf("%s%s",s1,s2);
        //printf("%c",s1);
       // cout<<'1'<<endl;
        if(!strcmp(s1,"-"))
            rch[i]=-1;
        else
        {
            rch[i]=s1[0]-'0';
            st.insert(rch[i]);
        }

        if(!strcmp(s2,"-"))
            lch[i]=-1;
        else
        {
            lch[i]=s2[0]-'0';
            st.insert(lch[i]);
        }
    }
    int root;
    for(int i=0;i<N;i++)
    {
        if(st.find(i)==st.end())
        {
            root=i;
            break;
        }
    }
    bfs(root);
    dfs(root);
    for(int i=0;i<N-1;i++)
    {
        cout<<level_order[i]<<' ';
    }
    cout<<level_order[N-1]<<endl;
    for(int i=0;i<N-1;i++)
    {
        cout<<in_order[i]<<' ';
    }
    cout<<in_order[N-1];
}

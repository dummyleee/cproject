#include <iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
int lch[101],rch[101];
vector<int> value,level;
int N;
map<int,int> in;
bool isroot[101];
int cnt=0;
void inorder(int root)
{
    if(lch[root]) inorder(lch[root]);
    //in.push_back(root);
    in[root]=cnt++;
    if(rch[root]) inorder(rch[root]);
}
void bfs(int root)
{
    queue<int> q;
    q.push(root);
    level.push_back(root);
    while(!q.empty())
    {
        int cur =q.front();
        q.pop();
        if(lch[cur])
        {
            q.push(lch[cur]);
            level.push_back(lch[cur]);
        }
        if(rch[cur])
        {
            q.push(rch[cur]);
            level.push_back(rch[cur]);
        }
    }
}
int main()
{
    freopen("1.txt","r",stdin);
    scanf("%d",&N);
    for(int i =0;i<N;i++)
    {
        int c1,c2;
        scanf("%d%d",&c1,&c2);
        if(c1!=-1)
        {
            lch[i] = c1;
            isroot[c1] = true;
        }
        if(c2!=-1)
        {
            rch[i] = c2;
            isroot[c2] = true;
        }

    }
    int root=0;
    for(int i=0;i<N;i++)
    {
        int key;
        scanf("%d",&key);
        value.push_back(key);
        if(!isroot[i])
            root=i;
    }
    sort(value.begin(),value.end());
    inorder(root);
    bfs(root);
    cout<<value[in[level[0]]];
    for(int i=1;i<N;i++)
    {
        cout<<' '<<value[in[level[i]]];
    }
    return 0;
}

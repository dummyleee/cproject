#include <iostream>
#include<map>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;
int lch[31];
int rch[31];
map<int,int> idtovalue;
map<int,int> valuetoid;
vector<int> post_order;
int N;
int build(int l1,int r1, int l2,int r2)
{
    if(r1<l1)
        return 0;
    int root = post_order[r2];
   // cout<<root<<endl;
    lch[root] = build(l1,root-1,l2,l2+root-l1-1);
    rch[root] = build(root+1,r1,l2+root-l1,r2-1);
    return root;
}
vector<int> level[31];
int book[31];
int max_level =0;
void new_bfs(int root)
{
    queue<int> q;
    q.push(root);
  //  level[root]=0;
   // level_order.push_back(root);
   level[0].push_back(root);
   book[root] = 0;
    while(!q.empty())
    {
        int cur =q.front();
        q.pop();
        int nl=book[cur]+1;
       // cout<<nl<<endl;
        if(lch[cur])
        {
            q.push(lch[cur]);
            level[nl].push_back(lch[cur]);
            book[lch[cur]] = nl;
            if(nl>max_level)
                max_level = nl;
        }
        if(rch[cur])
        {
            q.push(rch[cur]);
            level[nl].push_back(rch[cur]);
            book[rch[cur]]=nl;
            if(nl>max_level)
                max_level = nl;
        }
    }
   // cout<<level[1][1]<<endl;
}
int main()
{
    ifstream cin("1.txt");
    cin>>N;
    int cnt=1;
    for(int i=0;i<N;i++)
    {
        int node;
        cin>>node;
        idtovalue[cnt] = node;
        valuetoid[node] =cnt;
        cnt++;
    }
    for(int i=0;i<N;i++)
    {
        int node;
        cin>>node;
        post_order.push_back(valuetoid[node]);
    }
    //cout<<"1";
   // cout<<post_order[7];
    build(1,N,0,N-1);
   // cout<<lch[5]<<rch[5]<<endl;
    new_bfs(post_order[N-1]);
    cout<<idtovalue[post_order[N-1]];
    for(int i=1;i<=max_level;i++)
    {
        if(i%2)
            for(int j=0;j<level[i].size();j++)
            {
                cout<<' '<<idtovalue[level[i][j]];
            }
        else
            for(int j=level[i].size()-1;j>=0;j--)
            {
                cout<<' '<<idtovalue[level[i][j]];
            }
    }
    return 0;
}

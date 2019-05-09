#include <iostream>
#include<stack>
#define max_n 31
#include<string.h>
#include<vector>
using namespace std;
int lch[max_n],rch[max_n],value[max_n];
//int pre_order[max_n];
vector<int> in_order;
int N;
/*
int build(int l1,int l2,int r1,int r2)
{
    if(l1>l2)return 0;
    int root = l1;
    int root_id;
    for(int i=r1;i<=r2;i++)
    {
        if(in_order[i]==root)
        {
            root_id=i;
            break;
        }
    }
   // cout<<root_id<<endl;
    int l_size=root_id-r1;
    int r_size=r2-root_id;
    lch[root] = build(l1+1,l1+l_size,r1,root_id-1);
    rch[root] = build(l1+l_size+1,l2,root_id+1,r2);
    return root;
}
void dfs(int s)
{
    if(lch[s])
        dfs(lch[s]);
    if(rch[s])
        dfs(rch[s]);
    if(s!=1)
        cout<<value[s]<<' ';
}
*/
vector<int> post_order;
void post_dfs(int root,int start,int e)
{
  // cout<<root<<endl;
    if(start>e)
        return ;
    int root_id;
    for(int i=start;i<=e;i++)
    {
        if(in_order[i]==root)
        {
            root_id=i;
            break;
        }
    }
   //cout<<root_id;
    post_dfs(root+1,start,root_id-1);
    post_dfs(root+root_id-start+1,root_id+1,e);
    post_order.push_back(root);
}
int main()
{
    freopen("1.txt","r",stdin);
    stack<int> s;
    cin>>N;
    int cur=0;
    for(int i=0;i<2*N;i++)
    {
        char c[5];
        scanf("%s",c);
      //  printf("%s",c);
        if(!strcmp(c,"Push"))
        {
            int key;
            scanf("%d",&key);
      //      printf("%d\n",key);
            cur++;
            s.push(cur);
            value[cur] = key;
         //   pre_order[cur] = cur;
        }else if(!strcmp(c,"Pop"))
        {
            int a=s.top();
            s.pop();
            in_order.push_back(a);
        }
    }
   // for(int i=0;i<cur;i++)
   //     cout<<in_order[i]<<' ';
   // build(1,cur,0,cur-1);
   // cout<<'1'<<endl;
   //cout<< value[1];
    //dfs(1);
    post_dfs(1,0,cur-1);
    for(int i=0;i<post_order.size()-1;i++)
        cout<<value[post_order[i]]<<' ';
    cout<<value[1];
    return 0;
}

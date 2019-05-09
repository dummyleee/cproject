#include <iostream>
#include<vector>
using namespace std;
int N;
vector<int> pre,post,post2;
bool flag=false;
void postorder(int start,int e)
{
    if (start>e||flag) return;
    int root = pre[start];
   // int root_id = start;
    int i=start+1;
    while(pre[i]<root) i++;
    //cout<<i<<endl;
    for(int j=i-1;j<=e;j++)
        if(pre[j]<root)
        {
            flag=true;
            return;
        }
    postorder(start+1,i-1);
    postorder(i,e);
    post.push_back(root);
}
bool flag2 =false;
void postorder2(int start,int e)
{
    if (start>e||flag2) return;
    int root = pre[start];
   // int root_id = start;
    int i=start+1;
    while(pre[i]>=root) i++;
   // cout<<i<<endl;
    for(int j=i-1;j<=e;j++)
        if(pre[j]>=root)
        {
            flag2=true;
            return;
        }
    postorder2(start+1,i-1);
    postorder2(i,e);
    post2.push_back(root);
}
int main()
{
    freopen("1.txt","r",stdin);
    scanf("%d",&N);
   // cout<<N<<endl;
   pre.resize(N);
    for(int i=0;i<N;i++)
    {
        scanf("%d", &pre[i]);
    }
    //cout<<"1"<<endl;
    postorder(0,N-1);
    postorder2(0,N-1);
    if(flag&&flag2)
        cout<<"NO";
    else
    {
        if(flag)
            post =post2;
        cout<<"YES"<<endl;
        cout<<post2[0];
        for(int i=1;i<N;i++)
            cout<<' '<<post2[i];
    }
    return 0;
}

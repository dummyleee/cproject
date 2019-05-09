#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
vector<int> in_order;
int N;
int level[1010];
void build(int start,int e,int index)
{
    if(start>e)return ;
    int n=e -start+1;
    int k = log(n)/log(2);
    int left =pow(2,k-1)-1;
    int leave = min((int)(n-pow(2,k)+1),(int)pow(2,k-1));
    int root = start+leave+left;
    cout<<in_order[root]<<endl;
    level[index]=in_order[root];
    build(start,root-1,2*index);
    build(root+1,e,2*index+1);
}
int main()
{
    freopen("1.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;i++)
    {
        int key;
        scanf("%d",&key);
        in_order.push_back(key);
    }
    sort(in_order.begin(),in_order.end());
    build(0,N-1,1);
    for(int i=1;i<=N;i++)
        cout<<level[i]<<' ';
}
/*
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 1100
int n,a[maxn],b[maxn];
void create(int node,int &index)
{
    if(node>n) return;
    create(node<<1,index);
    cout<<node<<endl;
    a[node]=b[index++];
    create(node<<1|1,index);
}
int main()
{
    freopen("1.txt","r",stdin);
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;i++)
            scanf("%d",b+i);
        sort(b,b+n);
        int index=0;
        create(1,index);
        for(int i=1;i<=n;i++)
        {
            if(i>1) printf(" ");
            printf("%d",a[i]);
        }
        printf("\n");
    }
    return 0;
}
*/

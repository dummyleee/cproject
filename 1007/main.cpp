#include <iostream>

using namespace std;
int N;
int value[10001];
int start[10001],e[100001];
int sum[10001];
int main()
{
    freopen("1.txt","r",stdin);
    scanf("%d", &N);
    for(int i=1;i<=N;i++)
    {
        int key;
        scanf("%d",&key);
        value[i] = key;
    }
    sum[1] =value[1];
    start[1] = 1;
    e[1] =1;
    for(int i=2;i<=N;i++)
    {
       if(sum[i-1]+value[i]>value[i])
        {
            sum[i] = sum[i-1]+value[i];
            start[i] =start[i-1];
            e[i] =i;
        }
        else
        {
            sum[i] = value[i];
            start[i] =i;
            e[i]=i;
        }
    }
    int max_sum =sum[1];
    int min_d =0;
    int u=1;
    for(int i=2;i<=N;i++)
    {
        if(sum[i]>max_sum)
        {
            max_sum = sum[i];
            min_d = e[i] -start[i];
            u =i;
        }
        if(sum[i]==max_sum)
        {
           // cout<<min_d<<endl;
            if(min_d>e[i]-start[i])
            {
              min_d = e[i] -start[i];
              u =i;
            }
        }
    }

    if(max_sum<0)
    {
        cout<<"0 "<<value[1]<<' '<<value[N];
    }
    else
    {
        cout<<max_sum<<' '<<value[start[u]]<<' '<<value[e[u]];
    }
    return 0;
}

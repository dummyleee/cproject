#include <iostream>
#include<algorithm>
#include<vector>
using namespace std;
int N;
vector<int> in;
vector<int> pre_order;
int level[1001];
int order[1001];
int max_level =0;
void levelorder(int index,int start,int e)
{
    if(start>e) return ;
    int min_order = 1010;
    int root;
     for(int i=start;i<=e;i++)
     {
         if(min_order>order[i])
         {
             min_order = order[i];
             root =i;
         }
     }

     level[index]++;
     if(index>max_level)
        max_level=index;
     levelorder(index+1,start,root-1);
     levelorder(index+1,root+1,e);
}
int main()
{
    freopen("1.txt","r",stdin);
    scanf("%d",&N);
    for(int i=0;i<N;i++)
    {
        int key;
        scanf("%d",&key);
        in.push_back(key);
        pre_order.push_back(key);
    }

    sort(in.begin(),in.end());
    for(int i=0;i<=N;i++)
    {
        for(int j=N-1;j>=0;j--)
        {
            if(pre_order[i]==in[j]&&order[j]==0)
            {
                order[j] = i;
                break;
            }
        }
    }
    cout<<order[1]<<' '<<order[2]<<endl;
    levelorder(0,0,N-1);
    if(max_level==0)
        cout<<"1 + 0 = 1";
    else
    {
        cout<<level[max_level]<<" + "<<level[max_level-1]<<" = "<<level[max_level]+level[max_level-1];
    }
    return 0;
}

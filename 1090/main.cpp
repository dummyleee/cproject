#include <iostream>
#include<vector>
#include<stdio.h>
//#include<fstream>
using namespace std;
vector<int> supply[10000];
int N;
double p,r;
int max_num=0;
double max_sum=0;
int root;
void dfs(int s,double sum)
{
    //int new_sum=sum;
    if(s!=root)
        sum = sum*(1+r/100);
    if(supply[s].size()==0)
    {
        if(sum>max_sum)
        {
            max_num=1;
            max_sum=sum;
        }
        else if(sum==max_sum)
        {
            max_num++;
        }
    }
    for(int i=0;i<supply[s].size();i++)
        dfs(supply[s][i],sum);
}
int main()
{
   // ifstream cin("1.txt");
    freopen("1.txt","r",stdin);
    scanf("%d %lf %lf",&N, &p, &r);
    //scanf("%d %lf %lf", &n, &p, &r);
   // cout<<p<<endl;
    for(int i=0;i<N;i++)
    {
        int f;
        //cin>>f;
        scanf("%d",&f);
        if(f==-1)
        {
            root=i;
            continue;
        }
        supply[f].push_back(i);
    }
    dfs(root,p);
    printf("%.2f %d",max_sum,max_num);
    return 0;
}

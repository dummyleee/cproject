#include <iostream>
#include<map>
using namespace std;
map<int,int> C,M,E,A;
int N;
int getindex(int id,int i)
{
    map<int,int> m;
    if(i==0)
        m=A;
    if(i==1)
        m=C;
    if(i==2)
        m=M;
    if(i==3)
        m=E;
    int index=1;
    for(auto it=m.begin();it!=m.end();it++)
    {
        if(m[id]<it->second)
            index++;
    }
    return index;
}
int main()
{
    int num;
    freopen("1.txt","r",stdin);
    scanf("%d%d",&N,&num);
    for(int i=0;i<N;i++)
    {
        int id,ga,gm,ge,gav;
        scanf("%d%d%d%d",&id,&ga,&gm,&ge);
        gav = (ga+gm+ge)/3;
        C[id] = ga;
        M[id] = gm;
        E[id] = ge;
        A[id] = gav;
    }
    for(int i=0;i<num;i++)
    {
        int id;
        scanf("%d",&id);
        if(C.find(id)==C.end())
        {
            cout<<"N/A"<<endl;
            continue;
        }
        int best_rank=N+1,u;
        for(int j=0;j<4;j++)
        {
            int index=getindex(id,j);
            if(index<best_rank)
            {
                best_rank = index;
                u=j;
            }
        }
        cout<<best_rank<<' ';
        if(u==0) cout<<'A';
        if(u==1) cout<<'C';
        if(u==2) cout<<'M';
        if(u==3) cout<<'E';
        if(i!=num-1)
            cout<<endl;
    }
}

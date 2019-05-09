#include <iostream>
#include<iomanip>
#include<set>
using namespace std;
set<int> res[51];
int main()
{
    freopen("1.txt","r",stdin);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int k;
        scanf("%d",&k);
        while(k--)
        {
            int value;
            scanf("%d",&value);
            res[i].insert(value);
        }
    }
    int q;
    scanf("%d",&q);

    //set<int> total;
    while(q--)
    {*it
        int sum=0;
        int v1,v2;
        scanf("%d%d",&v1,&v2);
        for(auto it=res[v1].begin();it!=res[v1].end();it++)
        {
           if(res[v2].count(*it))
                sum++;
        }
        float r = 1.0*sum/(res[v1].size()+res[v2].size()-sum);
       // cout<<setiosflags(ios::fixed)<<setprecision(1)<<int((r*100+0.05)*10)/10.0<<'%'<<endl;
        r = int((r*100+0.05)*10)/10.0;
        printf("%.1f%%\n",r);
     //   total.clear();
    }

}

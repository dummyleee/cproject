#include <iostream>
#include<vector>
#include<iomanip>
#include<fstream>
#include<math.h>
using namespace std;
#define max_v 100000
vector<int> g[max_v];
int level[max_v];
int N;
void dfs(int s,int height)
{
    level[s] = height;
    for(int i=0;i<g[s].size();i++)
    {
        dfs(g[s][i], height+1);
    }
}
int main()
{
    ifstream cin("1.txt");
    double p,r;
    cin>>N>>p>>r;
    int sale[N];
    fill(sale,sale+N,0);
    for(int i=0;i<N;i++)
    {
        int k;
        cin>>k;
        if(k==0)
        {
            int s;
            cin>>s;
            sale[i] = s;
        }
        while(k--)
        {
            int id;
            cin>>id;
            g[i].push_back(id);
        }
    }
    dfs(0,0);
    double sum =0;
    for(int i=0;i<N;i++)
    {
        sum+=sale[i]*p*pow(1+0.01*r,level[i]);
    }
    cout<<setiosflags(ios::fixed)<<setprecision(1)<<int((sum+0.05)*10)/10.0;
    return 0;

}

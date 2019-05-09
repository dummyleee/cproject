#include <iostream>
#include<fstream>
#include<queue>
using namespace std;
bool vis[1287][129];
bool slice[1287][129];
int M,N,T;
int dt[2][8]={{-1,-1,-1,0,0,1,1,1},{-1,0,1,-1,1,-1,0,1}};
//int dt[2][8]={{-1,-1,0,1,1,1,0,-1},{0,-1,-1,-1,0,1,1,1}};
int bfs(int i,int j)
{
    int total=1;
    queue<int> q;
    int id =i*N+j-1;
    q.push(id);
    vis[i][j] = 1;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        int cur_i = cur/N;
        int cur_j = cur%N+1;
        for(int m=0;m<8;m++)
        {
            int next_i = cur_i+dt[0][m];
            int next_j = cur_j+dt[1][m];
            if(next_i>0&&next_i<=M)
            {
                if(next_j>0&&next_j<=N)
                {
                    if(!vis[next_i][next_j]&&slice[next_i][next_j])
                    {
                        cout<<next_i<<' '<<next_j<<endl;
                        q.push(next_i*N+next_j-1);
                        vis[next_i][next_j] = 1;
                        total++;
                    }
                }
            }
        }
    }
  //  cout<<endl;
    return total;

}
int main()
{
    ifstream cin("1.txt");
    int L;
    cin>>M>>N>>L>>T;
    int total=0;
    while(L--)
    {
    for(int i=1;i<=M;i++)
    {
        for(int j=1;j<=N;j++)
        {
            bool s;
            cin>>s;
            slice[i][j]=s;
            vis[i][j] =0;
        }
    }

    for(int i=1;i<=M;i++)
    {
        for(int j=1;j<=N;j++)
        {
            if(!vis[i][j]&&slice[i][j])
            {
              //  cout<<i<<' '<<j<<endl;
                int cur=bfs(i,j);
                //cout<<cur<<endl;
                if(cur>=T)
                    total+=cur;
            }
        }
    }
    }
    cout<<total<<endl;

}

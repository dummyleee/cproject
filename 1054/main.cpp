#include <iostream>
#include <map>
#include <fstream>
using namespace std;

int main()
{
    int m,n;
    cin>>m>>n;
    map<int,int> mp;
    int f =(m*n+1)/2;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
           int cur;
           scanf("%d", &cur);
           mp[cur]++;
           if(mp[cur]>f)
           {
               cout<<cur;
               return 0;
           }
        }
    }
}

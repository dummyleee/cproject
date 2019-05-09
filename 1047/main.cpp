/*
#include <iostream>
#include<map>
#include<set>
#include<string.h>
using namespace std;
int main()
{

    int n,k;
    scanf("%d%d",&n,&k);
    set<string> m1[k+1];
    while(n--)
    {
        char a[4];
        scanf("%s",&a);
        string name = a;
        int m;
        scanf("%d",&m);
        while(m--)
        {
            int id;
            scanf("%d", &id);
            m1[id].insert(name);
        }
    }
    for(int i=1;i<=k;i++)
    {
        cout<<i<<' '<<m1[i].size()<<endl;
        for(auto it =m1[i].begin();it!=m1[i].end();it++)
        {
            char b[4];
            string c = *it;
            strcpy(b,c.c_str());
            printf("%s\n",&b);
        }
    }
    return 0;
}
*/
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
char name[40001][4];
vector<int> course[2010];
bool cmp1(int a,int b)
{
    return strcmp(name[a],name[b])<0;
}
int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
   // vector<int> course[k];变量不能申明数组
    for(int i=1;i<=n;i++)
    {
       int c;
      int id;
       scanf("%s %d",name[i],&c);
       for(int j=0;j<c;j++)
       {

           scanf("%d",&id);
           course[id].push_back(i);
       }
    }
    for(int i=1;i<=k;i++)
    {
        cout<<i<<' '<<course[i].size()<<endl;
        sort(course[i].begin(),course[i].end(),cmp1);
        for(int j=0;j<course[i].size();j++)
        {
            printf("%s\n",name[course[i][j]]);
        }
    }
}


/*
#include <iostream>
#include<set>
#include<fstream>
using namespace std;
set<int> s;
int main()
{
    ifstream cin("1.txt");
    int N,M;
    cin>>N>>M;
    int v1=M;
    int v2=0;
    for(int i=0;i<N;i++)
    {
        int cur;
        cin>>cur;
        for(auto it=s.begin();it!=s.end();it++)
        {
            int total =*it+cur;
            if(total==M)
            {
                int min_d =*it>cur?cur:*it;
                int max_d =*it>cur?*it:cur;
                if(min_d<v1)
                {
                    v1=min_d;
                    v2=max_d;
                }

            }else if(total>M)
            {
                break;
            }
        }
        s.insert(cur);
    }
    if(v2==0)
        cout<<"No Solution";
    else
        cout<<v1<<' '<<v2;
    return 0;
}
*/
#include<iostream>
#include<fstream>
using namespace std;
int a[1001];
int main()
{
    ifstream cin("1.txt");
    int N,M;
    cin>>N>>M;
    for(int i=0;i<N;i++)
    {
        int temp;
        cin>>temp;
        a[temp]++;
    }
    for(int i=1;i<=500;i++)
    {
        if(M==2*i&&a[i]<2)
        {

            cout<<"No Solution";
            return 0;
        }
        if(a[i]>0&&a[M-i]>0)
        {
            cout<<i<<' '<<M-i;
            return 0;
        }
    }
    cout<<"No Solution";
    return 0;
}
/*别人的解法
#include <iostream>
using namespace std;
int a[1001];
int main() {
    int n, m, temp;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &temp);
        a[temp]++;
    }
    for(int i = 0; i < 1001; i++) {
        if(a[i]) {
            a[i]--;
            if(m > i && a[m-i]) {
                printf("%d %d", i, m - i);
                return 0;
            }
            a[i]++;
        }
    }
    printf("No Solution");
    return 0;
}*/

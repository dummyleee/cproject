#include <iostream>

using namespace std;
int a[10001];
int b[100001];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int m;
        scanf("%d",&m);
        b[i] =m;
        a[m]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(a[b[i]]==1)
        {
            cout<<b[i];
            return 0;
        }
    }
    cout<<"None";
    return 0;

}

#include <iostream>
#include<time.h>

using namespace std;
void f(int a[])
{
    a[1] =3;
}
void merges(int a[],int b[],int l1,int l2)
{
    int c[l1+l2];
    int i = 0,j=0,k=0;
    while(i<l1&&j<l2)
    {
        if(a[i]>b[j])
        {
            c[k++] = b[j++];
        }
        else
            c[k++] = a[i++];
    }
    while(i<l1)
        c[k++] = a[i++];
    while(j<l2)
        c[k++] = b[j++];
    cout<<k<<endl;
}
int main()
{
    int a[4] = {1,3,6,8};
    int b[3] = {2,5,6};
    merges(a,b,4,3);
   // cout<<a[1]<<endl;
}

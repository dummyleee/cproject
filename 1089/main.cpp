/*
#include <iostream>
#include<algorithm>
using namespace std;
int N;
int num[100];
int res[100];
bool flag=false;
bool
bool cmp(int a[],int b[])
{
    for(int i=0;i<N;i++)
        if(a[i]!=b[i])
        return false;
    return true;
}
void insertsort()
{

    int key =1;
    for(int i=1;i<N;i++)
    {
        if(flag = true)
        key = i;
       while(num[key]<num[key-1]&&key>0)
       {
           int temp = num[key];
           num[key]=num[key-1];
           num[key-1] = temp;
           key--;
           if(cmp(num,res))
           {
               flag = true;
           }
       }
    }
}
int main()
{
    freopen("1.txt","r",stdin);
    scanf("%d",&N);
    int key;
    for(int i=0;i<N;i++)
    {

        scanf("%d",&key);
        num[i]=key;
    }
    //cout<<N<<endl;
    for(int i=0;i<N;i++)
    {
        scanf("%d",&key);
        res[i]=key;
    }
    insertsort();
    if(flag)
        cout<<"Insertion Sort"<<endl;
    else
        cout<<"Merge Sort"<<endl;
    sort(num,num+N);
    cout<<num[0];
    for(int i=1;i<N;i++)
    {
        cout<<' '<<num[i];
    }
    return 0;
}
*/

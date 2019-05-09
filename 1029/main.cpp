/*
#include<iostream>
#include<queue>
#include<fstream>
using namespace std;

int main()
{
    ifstream cin("1.txt");
    queue<long int> q1,q2;
    int n1;
    int n2;
    long int key;
    cin>>n1;
    for(int i=0;i<n1;i++)
    {
        cin>>key;
        q1.push(key);
    }
    cin>>n2;
    for(int j=0;j<n2;j++)
    {
        cin>>key;
        q2.push(key);
    }
    int index=0;
    int md;
    for(;;)
    {
        if(q1.empty())
        {
            md = q2.front();
            q2.pop();
            index++;
        }
        else if(q2.empty())
        {
            md = q1.front();
            q1.pop();
            index++;
        }else
        {
            if(q1.front()>q2.front())
            {
                md = q2.front();
                q2.pop();
            }
            else
            {
                md =q1.front();
                q1.pop();
            }
            index++;
        }
        if(index==(n1+n2+1)/2)
            break;
    }
    cout<<md;

}
*/
#include<iostream>
#include<fstream>
#define INF 99999999
using namespace std;
long int s[200005];
int main()
{
    int n1;
    int n2;
    long int key;
    cin>>n1;
    for(int i=0;i<n1;i++)
    {
        cin>>key;
        s[i] =key;
    }
    s[n1] = INF;
    cin>>n2;
    int temp=0;
    int index=0
    int median = (n1+n2+1)/2;
    int md;
    for(;;)
    {
        index++;
      //  temp++;
        if(index>n2)
            key = INF;
        else
            cin>>key;
        if(temp+index==median)
        {
            md = key;
            break;
        }
        while(s[temp]<=key&&temp<median-index)
        {
            if()
        }
        if(temp+index==median)
        {

        }
    }
}

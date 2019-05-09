#include <iostream>
#include<map>
#include<fstream>
#include<sstream>
using namespace std;
int change(string time)
{
    stringstream ss;
    int hour,minute,miao;
    string s1 =time.substr(0,2);
    string s2 =time.substr(3,5);
    string s3 =time.substr(6);
    ss<<s1;
    ss>>hour;
    ss<<s2;
    ss>>minute;
    ss<<s3;
    ss>>miao;
    return hour*3600+minute*60+miao;
}
bool cmp(string time1,string time2)
{
    if(time1=="1"||time2=="-1")
    {
        return true;
    }
    if(time1=="-1"||time2=="1")
        return false;
    int t1 = change(time1);
    int t2 = change(time2);
    if(t1>t2)
        return true;
    else
        return false;

}
map<string,string>lock;
map<string,string>unlock;
int main()
{
    ifstream cin("1.txt");
    int M;
    cin>>M;
    while(M--)
    {
        string id,time1,time2;
        cin>>id>>time1>>time2;
        if(unlock.find(id)!=unlock.end())
        {
            if(cmp(unlock[id],time1))
            {
                unlock[id] = time1;
            }
            if(cmp(time2,lock[id]))
                lock[id] = time2;
        }
        else
        {
            unlock[id] = time1;
            lock[id] =time2;
        }
    }
    string min_t ="1";
    string max_t ="-1";
    string id1,id2;
    for(auto it=unlock.begin();it!=unlock.end();it++)
    {
       // cout<<it->second<<endl;
        if(cmp(min_t,it->second))
        {
            min_t = it->second;
            id1 = it->first;
        }
    }
    for(auto it=lock.begin();it!=lock.end();it++)
    {
        if(cmp(it->second, max_t))
        {
            max_t = it->second;
            id2 = it->first;
        }
    }
    cout<<id1<<' '<<id2;
    return 0;
}

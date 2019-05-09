/*
#include <iostream>
#include<fstream>
#include<map>
#include<set>
#include<vector>
#include<sstream>
using namespace std;

int main()
{
    fstream cin("1.txt");
    int n;
    cin>>n;
    cin.get();
    map<int, string> title;
    map<int,string> author;
    map<string,set<int>> keyword;
    map<int, string> pub;
    map<int, string> year;
    while(n--)
    {
        int ID;
        cin>>ID;
        cin.get();
        string ts,as,ks,ps,ys;
        getline(cin,ts);
        title[ID] = ts;
        getline(cin,as);
        author[ID] = as;
        getline(cin,ks);
        while(int(ks.find(' '))>0)
        {
            int p = ks.find(' ');
            keyword[ks.substr(0,p)].insert(ID);
            ks = ks.substr(p+1);
        }
        keyword[ks].insert(ID);
        getline(cin,ps);
        pub[ID] = ps;
        getline(cin,ys);
        year[ID] = ys;
    }
    int m;
    cin>>m;
    cin.get();
    for(int i=0;i<m;i++)
    {
        string query;
        string num;
        getline(cin, query);
        cout<<query<<endl;
        num = query.substr(0,1);
        string query1 = query.substr(3);
        if(num=="1")
        {
            map<int, string>::iterator itor = title.begin();
            int flag=0;
            while(itor!=title.end())
            {
                if(itor->second==query1)
                {
                    cout<<itor->first<<endl;
                    flag = 1;
                }
                itor++;
            }
            if(!flag)
            {
                cout<<"Not Found"<<endl;
            }

        }
        if(num=="2")
        {
            int flag = 0;
            map<int, string>::iterator itor = author.begin();
            while(itor!=author.end())
            {

                if(itor->second==query1)
                {
                    cout<<itor->first<<endl;
                    flag =1;
                }
                itor++;
            }
            if(!flag)
            {
               cout<<"Not Found"<<endl;
            }
        }
        if(num=="3")
        {
            if(keyword.find(query1)!=keyword.end())
            {
                set<int>::iterator itor = keyword[query1].begin();
                while(itor!=keyword[query1].end())
                {
                    cout<<*itor<<endl;
                    itor++;
                }
            }
            else
            {
                cout<<"Not Found"<<endl;
            }
        }
        if(num=="4")
        {
            int flag = 0;
            map<int, string>::iterator itor = pub.begin();
            while(itor!=pub.end())
            {

                if(itor->second==query1)
                {
                    cout<<itor->first<<endl;
                    flag =1;
                }
                itor++;
            }
            if(!flag)
            {
                cout<<"Not Found"<<endl;;
            }
        }
        if(num=="5")
        {
            int flag =0;
            map<int, string>::iterator itor = year.begin();
            while(itor!=year.end())
            {

                if(itor->second==query1)
                {
                    cout<<itor->first<<endl;
                    flag =1;
                }
                itor++;
            }
            if(!flag)
            {
                cout<<"Not Found"<<endl;;
            }
        }
    }
    return 0;
}
*/
#include<iostream>
#include<map>
#include<set>
#include<fstream>
#include<iomanip>
using namespace std;
void search_m(map<string,set<int>> m, string s)
{
    if(m.find(s)!=m.end())
    {
        for(auto it=m[s].begin();it!=m[s].end();it++)
        {
            cout<<setw(7)<<setfill('0')<<*it<<endl;
        }
    }
    else
        cout<<"Not Found"<<endl;
}
int main()
{
    ifstream cin("1.txt");
    int n;
    cin>>n;
    cin.get();
    map<string, set<int>> title,author,keyword,pub,year;
    while(n--)
    {
        int ID;
        cin>>ID;
        cin.get();
        string ts,as,ks,ps,ys;
        getline(cin,ts);title[ts].insert(ID);
        getline(cin,as);author[as].insert(ID);
        while(cin>>ks)
        {
            keyword[ks].insert(ID);
            char c =cin.get();
            if(c=='\n')
            {
                break;
            }
        }
        getline(cin,ps);pub[ps].insert(ID);
        getline(cin,ys);year[ys].insert(ID);
    }
    int m;
    cin>>m;
    cin.get();
    while(m--){
        string query;
        getline(cin, query);
        string num = query.substr(0,1);
        string query1 = query.substr(3);
        cout<<query<<endl;
        if(num=="1")
            search_m(title, query1);
        else if(num=="2")
            search_m(author,query1);
        else if(num=="3")
            search_m(keyword,query1);
        else if(num=="4")
            search_m(pub, query1);
        else
            search_m(year, query1);
        }
    return 0;
}

#include <iostream>
#include<vector>
#include<map>
#include<set>
#include<fstream>
using namespace std;

int main()
{
    ifstream cin("1.txt");
    int n,k;
    cin>>n>>k;
    map<string,set<int>> m;
    while(k--)
    {
        int id,num;
        cin>>id>>num;
        while(num--)
        {
            string name;
            cin>>name;
            m[name].insert(id);
        }
    }
    while(n--)
    {
        string name;
        cin>>name;
        if(m.find(name)!=m.end())
        {
            cout<<name<<' '<<m[name].size();
            for(auto it=m[name].begin();it!=m[name].end();it++)
                cout<<' '<<*it;
        }
        else
        {
            cout<<name<<' '<<'0';
        }
        cout<<endl;
    }
}

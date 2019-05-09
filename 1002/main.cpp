#include <iostream>
#include<fstream>
#include<map>
#include<iomanip>
using namespace std;

int main()
{
    ifstream cin("1.txt");
    map<int,float> m;
    int k;
    cin>>k;
    int coe;
    float exp;
    while(k)
    {
        cin>>coe>>exp;
        m[coe] = exp;
        k--;
    }
    cin>>k;
    while(k)
    {
        cin>>coe>>exp;
        map<int,float>::iterator itor =m.find(coe);
        if(itor!=m.end())
        {
            m[coe]+=exp;
        }
        else{
            m[coe] = exp;
        }
        k--;
    }
    map<int, float>::iterator itor2 =m.begin();
    while(itor2!=m.end()){
        if(itor2->second==0){
            m.erase(itor2->first);
        }
        itor2++;
    }
    cout<<m.size();
    map<int,float>::reverse_iterator itor = m.rbegin();
    while(itor!=m.rend())
    {
        cout<<' '<<itor->first<<' '<<setiosflags(ios::fixed)<<setprecision(1)<<itor->second;
        itor++;
    }
    return 0;
}

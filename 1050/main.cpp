#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int v[150];
int main()
{
    ifstream cin("1.txt");
    string s1,s2;
    vector<char> res;
    getline(cin, s1);
    getline(cin, s2);

    for(int i=0;i<s2.length();i++)
    {
        int id = s2[i]-' ';

        v[id]++;
    }
    for(int i=0;i<s1.length();i++)
    {
        int id = s1[i]-' ';
        if(v[id]==0)
        {
            res.push_back(s1[i]);
        }
    }
    for(auto it = res.begin();it!=res.end();it++)
        printf("%c",*it);
}

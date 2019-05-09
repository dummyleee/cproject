#include <iostream>
#include<vector>
#include<fstream>
using namespace std;
vector<string> m;
int main()
{
    ifstream cin("1.txt");
    int n;
    int s = -1;
    while(n--)
    {
        string op;
        cin>>op;
        if(op=="Pop")
        {
            if(s==-1)
                cout<<"Invalid"<<endl;
            else
            {
                cout<<m[s]<<endl;
                m.pop_back();
                s--;
            }
        }else if(op=="Push")
        {
            string key;
            cin>>key;
            m.push_back(key);
            s++;
        }else if(op=="PeekMedian")
        {
            if(s==-1)
                cout<<"Invalid"<<endl;
            else
            {
                int id=(s+1)/2;
                cout<<m[id]<<endl;
            }
        }
    }
}

/*
#include <iostream>
#include<set>
#include<fstream>
using namespace std;

int main()
{
    ifstream cin("1.txt");
    set<int> num;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int s;
        cin>>s;
        if(s<0)
            num.insert(0);
        else
            num.insert(s);
    }
    set<int>::iterator it;
    int res;
    for(it=num.begin();it!=num.end();)
    {
        int a =*it+1;
        it++;
        if(it==num.end())
        {
            cout<<a;
            return 0;
        }else
        {
            if(a!=*it)
            {
                cout<<a;
                return 0;
            }
        }

    }
    return 0;
}
*/
#include <iostream>
#include <map>
using namespace std;
int main() {
    int n, a, num = 0;
    cin >> n;
    map<int, int> m;
    for (int i = 0; i < n; i++) {
        cin >> a;
        m[a]++;
    }
    while(++num)
        if (m[num] == 0) break;
    cout << num;
    return 0;
}

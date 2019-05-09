/*
#include <iostream>
#include<map>
#include<vector>
#include<fstream>
#include<cctype>
using namespace std;
bool isalpha(char c)
{
    if((c<='9'&&c>='0')||(c>='A'&&c<='Z')||(c>='a'&&c<='z'))
        return true;
    else return false;
}
char a[1048576];
map<string,int> m;
void change(int i,int j)
{
  //  int cur_size=j-i;
    char cur[j-i];
    for(int n=i;n<j;n++)
    {
        if(a[n]>='A'&&a[n]<='Z')
        {
            a[n]=char(a[n]+32);
        }
        cur[n-i]=a[n];
    }
    string s = cur;
    m[s]++;
}
int main()
{
    ifstream cin("1.txt");
    string s;
    getline(cin,s,'\n');
    for(int i=0;i<s.length();i++)
        a[i] =s[i];
  //  int first,second;
    for(int i=0;i<s.length();i++)
    {

        if(isalpha(s[i]))
        {
            int first =i;
            i++;
            while(isalpha(s[i]))
                i++;
            int second =i;
            change(first,second);

        }
    }
    string max_s;
    int max_num =0;
    for(auto it=m.begin();it!=m.end();it++)
    {
        if(max_num<it->second)
        {
            max_s = it->first;
            max_num = it->second;
        }
    }
    cout<<max_s<<' '<<max_num;
    return 0;

}
*/
#include<iostream>
#include<map>
using namespace std;
bool isalpha(char c)
{
    if((c<='9'&&c>='0')||(c>='A'&&c<='Z')||(c>='a'&&c<='z'))
        return true;
    else return false;
}
int main(){
    string s;
    getline(cin,s);
    map<string,int> m;
    for(int i=0;i<s.length();i++)
    {
        if(isalpha(s[i]))
        {
            string cur ="";
            cur+=tolower(s[i]);
            i++;
            while(isalpha(s[i]))
            {
                cur+=tolower(s[i]);
                i++;
            }
            m[cur]++;
        }
    }
    int maxn = 0;
    string max_s;
    for(auto it = m.begin(); it != m.end(); it++) {
        if(it->second > maxn) {
            max_s = it->first;
            maxn = it->second;
        }
    }
    cout << max_s<< " " << maxn;
    return 0;

}




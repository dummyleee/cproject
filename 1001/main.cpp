/*
#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;

int main()
{
    ifstream cin("1.txt");
    int a,b;
    cin>>a>>b;
    int c;
    c= a+b;
    if (abs(c)>=1000000)
    {
        cout<<c/1000000<<','<<setfill('0')<<setw(3)<<abs(c)/1000%1000<<','<<setfill('0')<<setw(3)<<abs(c%1000)<<endl;
    }
    else if(abs(c)>=1000)
    {
        cout<<c/1000<<','<<setfill('0')<<setw(3)<<abs(c%1000)<<endl;
    }
    else
        cout<<c<<endl;
    return 0;
}
*/
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
int main(){
    ifstream cin("1.txt");
    int a,b;
    cin>>a>>b;
    int c = a+b;
    if(c<0)
        cout<<'-';
    string s;
    stringstream ss;
    ss<<abs(c);
    ss>>s;
    int len = s.length();
    //cout<<len<<endl;
    char res[len+(len-1)/3];
    int j = 0;
    for(int i=0;i<len+(len-1)/3;i++)
    {
        int postion = len+(len-1)/3 - i;
        if(postion!=0&&postion/4==double(postion)/4)
        {
            res[i]=',';
        }
        else
        {
            res[i] = s[j];
            j++;
        }
    }
    for(int i=0;i<len+(len-1)/3;i++)
    {
        cout<<res[i];
    }
    return 0;
}

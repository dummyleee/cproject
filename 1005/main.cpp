#include <iostream>
#include<sstream>
#include<fstream>
using namespace std;
void change(int a)
{
    switch(a){
    case 1:
        cout<<"one";
        break;
    case 2:
        cout<<"two";
        break;
    case 3:
        cout<<"three";
        break;
    case 4:
        cout<<"four";
        break;
    case 5:
        cout<<"five";
        break;
    case 6:
        cout<<"six";
        break;
    case 7:
        cout<<"seven";
        break;
    case 8:
        cout<<"eight";
        break;
    case 9:
        cout<<"nine";
        break;
    case 0:
        cout<<"zero";
        break;
    }
}
int main()
{
    ifstream cin("1.txt");
   string s;
   cin>>s;
   int sum = 0;
   for(int i=0;i<s.length();i++)
   {
       char c = s[i];
       int a = c-'0';
       sum += a;
   }

   if(sum>99)
   {
       change(sum/100);
       cout<<' ';
       change(sum/10%10);
       cout<<' ';
       change(sum%10);
   }
   else if(sum>9)
   {
       change(sum/10);
       cout<<' ';
       change(sum%10);
   }
   else{
    change(sum);
   }
   return 0;
}

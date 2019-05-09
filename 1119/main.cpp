//这道题是真的睿智，结果一定要加个换行要不然就是格式错误
#include <iostream>
#include<fstream>
#include<vector>
using namespace std;
int lch[31];
int rch[31];
vector<int>pre_order,in_order,post_order;
int N;
bool uq=true;
void build(int l1,int r1,int l2,int r2)
{
    //cout<<"1"<<endl;
    if(l1==r1)
    {
        in_order.push_back(pre_order[l1]);
        return;
    }
   // cout<<"1"<<endl;
    int root = pre_order[l1];
    int left_root = pre_order[l1+1];
   // cout<<left_root;
    int root_id ;
    for(int i=l2;i<r2;i++)
    {
        if(post_order[i]==left_root)
        {
            root_id = i;
            break;
        }
    }
   // cout<<root_id<<endl;
    if(root_id==r2-1)
    {
        uq = false;
        build(l1+1,r1,l2,r2-1);
        in_order.push_back(pre_order[l1]);
    }
    else
    {
        build(l1+1,l1+root_id-l2+1,l2,root_id);
        in_order.push_back(pre_order[l1]);
        build(l1+root_id-l2+2,r1,root_id+1,r2-1);
    }
}
int main()
{
    ifstream cin("1.txt");
    cin>>N;
    int cur;
    for(int i=0;i<N;i++)
    {

        cin>>cur;
      //  cout<<cur<<' ';
        pre_order.push_back(cur);
    }
    for(int i=0;i<N;i++)
    {
        cin>>cur;
        post_order.push_back(cur);
    }
    build(0,N-1,0,N-1);
    if(uq)
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;
    cout<<in_order[0];
    for(int i=1;i<N;i++)
        cout<<' '<<in_order[i];
    return 0;
}

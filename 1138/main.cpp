
#include <iostream>
#include<vector>
#include<map>
#include<fstream>
using namespace std;
map<int,int> idtovalue;
map<int,int> valuetoid;
int n;
vector<int> in_order,post_order;
void post_dfs(int root,int l1,int r1)
{
    if(l1>r1)
    {
    //    post_order.push_back(root);
        return;
    }
   // if(l1==r1)
    //{
     //   post_order.push_back(root);
      //  cout<<root<<' '<<in_order[l1]<<endl;
       // return;
    //}
    int root_id=l1;
    for(int i=l1;i<=r1;i++)
    {
        if(in_order[i]==root)
        {
            root_id = i;
            break;
        }
    }
    //cout<<root_id<<endl;
    post_dfs(root+1,l1,root_id-1);
    post_dfs(root+root_id-l1+1,root_id+1,r1);
    post_order.push_back(root);
}
int main()
{
    fstream cin("1.txt");
    cin>>n;
    int cnt=0;
    for(int i=0;i<n;i++)
    {
        int key;
        cin>>key;
        cnt++;
        valuetoid[key] = cnt;
        idtovalue[cnt] = key;
        //cnt++;
    }
    for(int i=0;i<n;i++)
    {
        int key;
        cin>>key;
        in_order.push_back(valuetoid[key]);
    }
   // for(int i=0;i<in_order.size();i++)
    //    cout<<in_order[i]<<' ';
   // cout<<"1"<<endl;
    post_dfs(1,0,cnt-1);
    cout<<idtovalue[post_order[0]];
    return 0;
}
/*
#include <iostream>
#include <vector>
using namespace std;
vector<int> pre, in,post;
bool flag = false;
void postOrder(int prel, int inl, int inr) {
    if (inl > inr || flag == true) return;
    int i = inl;
    while (in[i] != pre[prel]) i++;
   // cout<<in[i]<<' '<<pre[prel];
    cout<<i<<endl;
    postOrder(prel+1, inl, i-1);
    postOrder(prel+i-inl+1, i+1, inr);
    /*
    if (flag == false) {
        printf("%d", in[i]);
        flag = true;
    }

    post.push_back(pre[prel]);
}
int main() {
    freopen("1.txt","r",stdin);
    int n;
    scanf("%d", &n);
    pre.resize(n);
    in.resize(n);
    for (int i = 0; i < n; i++) scanf("%d", &pre[i]);
    for (int i = 0; i < n; i++) scanf("%d", &in[i]);
    postOrder(0, 0, n-1);
    cout<<post[0];
    return 0;
}
*/

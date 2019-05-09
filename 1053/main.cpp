#include <iostream>
#include <vector>
#include<algorithm>
#include<fstream>
using namespace std;
vector<int> tree[101];
int value[101];
vector<vector<int>> path;
int N,S;
int max_path=0;
vector<int> temppath;
void dfs(int s)
{
    temppath.push_back(s);

    if(tree[s].size()==0)
    {
        int total =0;
        for(int i=0;i<temppath.size();i++)
        {
            total+=value[temppath[i]];
        }
        if(total==S)
        {
            path.push_back(temppath);
            max_path++;
        }
    }
    for(int i=0;i<tree[s].size();i++)
    {
        dfs(tree[s][i]);
    }
    temppath.pop_back();
}
bool cmp1(vector<int> a,vector<int> b)
{

    int s1=a.size();
    int s2=b.size();
    int min_s = s1>s2?s2:s1;
    for(int i=0;i<min_s;i++)
    {
        if(value[a[i]]>value[b[i]])
            return true;
        if(value[a[i]]<value[b[i]])
            return false;
    }
    return false;

    //return a[2]>b[2];
}
/*
bool cmp(const vector<int> &a,const vector<int> &b){
	if(a==b)//注意STL的sort规定相等时必须返回false
		return false;
	int n=a.size();
	int m=b.size();
	int i=0;
	while(i<n&&i<m){
		if(a[i]>b[i])
			return true;
		else if(a[i]<b[i])
			return false;
		else
			i++;
	}
	if(i==m)
		return true;
	return false;
}*/
int main()
{
    ifstream cin("1.txt");
    int m;
    cin>>N>>m>>S;
    for(int i=0;i<N;i++)
    {
        cin>>value[i];
    }
    while(m--)
    {
        int id,k;
        cin>>id>>k;
        while(k--)
        {
            int child;
            cin>>child;
            tree[id].push_back(child);
        }
    }
    dfs(0);
    sort(path.begin(),path.end(),cmp1);
    for(int i=0;i<max_path;i++)
    {
        cout<<value[path[i][0]];
        for(int j=1;j<path[i].size();j++)
        {
            cout<<' '<<value[path[i][j]];
        }
        cout<<endl;
    }
}

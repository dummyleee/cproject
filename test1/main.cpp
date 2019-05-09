#include <iostream>
#include<set>
#include<algorithm>
using namespace std;
int board[11][11] = {0};
set<int> total;
void find_node(int i,int j){
    if(i<0||i>=11||j<0||j>=11)
        return ;
    if(board[i][j] == 2)
        return ;
    if(board[i][j] == 0)
        total.insert(i*11+j);
    if(board[i][j] == 1){
        find_node(i+1,j);
        find_node(i,j+1);
        find_node(i-1,j+1);
    }
}
void find_next(int i, int j){
    find_node(i+1,j);
    find_node(i,j+1);
    find_node(i-1,j+1);
}
struct Node { //定义表结点
  int adjvex; //该边所指向的顶点的位置
  int weight;// 边的权值
  Node *next; //下一条边的指针
};

struct HeadNode{ // 定义头结点
    int nodeName; // 顶点信息
    int inDegree; // 入度
    Node *link; //指向第一条依附该顶点的边的指针
};
int main()
{

    int i,j;
  Link adj[8];
  while(cin>>i>>j)
    {
        adj[j]=new node(i,adj[j]);
        adj[i]=new node(j,adj[i]);
    }

    for(i=0;i<8;i++)
    {
        cout<<i<<"\t";
        while(adj[i]->next!=NULL)
        {
            cout<<adj[i]->v<<"--->";
            adj[i]=adj[i]->next;
        }
        cout<<adj[i]->v<<endl;

    }
}

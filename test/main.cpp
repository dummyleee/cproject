#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include<queue>
#include<cmath>
#include<ctime>
#include<cstring>
//#include "define.h"
#define MAX 121
#define color 1
#define MAX_FLOW 999
using namespace std;
int board[11][11] = {0};
set<int> total;
int depth[MAX+2];
void find_node(int i,int j){
    if(i<0||i>=11||j<0||j>=11)
        return ;
    if(board[i][j] == (!color)+1)
        return ;
    if(board[i][j] == 0)
        total.insert(i*11+j+1);
    if(board[i][j] == 1){
        find_node(i+1,j);
        find_node(i,j+1);
        find_node(i-1,j+1);
    }
    if(board[i][j] == 2){
        find_node(i,j-1);
        find_node(i+1,j);
        find_node(i+1,j-1);
    }
}
void find_next(int i, int j){
    if(color == 1)
    {
        find_node(i+1,j);
        find_node(i,j+1);
        find_node(i-1,j+1);
    }
    else
    {
        find_node(i,j-1);
        find_node(i+1,j);
        find_node(i+1,j-1);

    }
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
HeadNode *G ;
/*
void printGraph(HeadNode *G) {

    for (int i = 0; i < MAX+2; i++) {
        mycout << "结点v" << G[i].nodeName << "的入度为";
        mycout << G[i].inDegree << ", 以它为起始顶点的边为: ";
        Node *node = G[i].link;
        while (node != NULL) {
            mycout << "v" << G[node->adjvex].nodeName << "(权:" << node->weight << ")" << "  ";
            node = node->next;
        }
        mycout << endl;
    }
    mycout.close();
}*/
void freeGraph(HeadNode *G)
{
    for(int i=0;i<MAX+2;i++)
    {
        Node*p1 =G[i].link;
        Node*p2;
        while(p1!= NULL)
        {
            p2 = p1->next;
            delete p1;
            p1 = p2;
        }
    }
    delete[] G;

}
int bfs(){
    queue<int> Q;
    while (!Q.empty())
        Q.pop();
    memset(depth,0,sizeof(depth));
    depth[0] = 0;
    Q.push(0);
    do
    {
        int u =Q.front();
        Q.pop();
        Node*node =G[u].link;
        while(node !=NULL)
        {

            if((node->weight > 0)&&(depth[node->adjvex] == 0))
            {
                depth[node->adjvex] = depth[u] + 1;
                Q.push(node->adjvex);
            }
            node =node->next;
        }
    }while(!Q.empty());
    if(depth[122]>0)
        return 1;
    return 0;
}
//如果(v,u)已经存在，则增加权重，否则增加一条边
void update(int v,int u,int d){
    Node*node =G[v].link;
    int flag = 0;
    while(!flag&&node!=NULL){
        if(node->adjvex == u)
        {
            node->weight +=d;
            flag =1;
        }
        else{
            node= node->next;
        }
    }
    if(!flag){
        Node *n = new Node;
        n->adjvex = u;
        n->weight = d;
        n->next = G[v].link;
        G[v].link = n;
    }

}
int dfs(int u,int dist){
    if(u==122)
        return dist;
    Node*node =G[u].link;
    while(node!=NULL){
        if((depth[node->adjvex]==depth[u]+1)&&(node->weight!=0))
        {
            int di = dfs(node->adjvex,dist < node->weight ? dist:node->weight);
            if(di>0)
            {
                node->weight = node->weight - di;
                update(node->adjvex,u,di);//反向边加权重
                return di;
            }
        }
        node = node->next;
    }
    return 0;
}
int Dinic(){
    ofstream mycout("test.txt");
    int ans = 0;
    while(bfs()){

        while(int d =dfs(0,MAX_FLOW)){

            ans+= d ;

        }
//        printGraph(G);
    }
    return ans;
}
struct State{
    int b[11][11];
    State *father;
    int c;
    int Q;
    int N;
    int line;
    int row;
    int childNum;//孩子结点总数
    int curChild;//已被扩展的孩子总数
    State *child[121];//已被扩展的孩子结点指针
    set<int> childSet;//未被扩展的孩子结点集合
    State()
    {
        Q = 0;
        N = 0;
        childNum = 0;
        curChild = 0;
    }
};
State*Expand(State*v){
    srand((unsigned)time(NULL));
    int id=rand()%(v->childNum - v->curChild)+0;
    set<int>::iterator it;
    int flag =0;
    int childID;
    for(it=v->childSet.begin();it!=v->childSet.end();it++){
        if(flag == id){
            childID = *it;
        }
        else
            flag++;
    }

    State *v1 =new State();
    v1->father = v;
    v1->c = (!v->c);
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            v1->b[i][j] = v->b[i][j]
            if(v->b[i][j] ==0)
                v1->childSet.insert(i*11+j)
        }
    }
    v1->childNum = v->childNum -1;
    int m = childID/11;
    int n = childID%11;
    v1->line = m;
    v1->row = n;
    v1->b[m][n] = v->c + 1;
    v1->childSet.erase(childID);
    v->child[v->curChild] = v1;
    v->curChild++;
    v->childSet.erase(childID);
    return v1;
}
State* BestChild(State*v,int a){
    double max_ucb = 0;
    State* best;
    if(v->c==color){
        for(int i=0;i<v->curChild;i++){
            State*cur = v->child[i];
            double ucb = double(cur->Q)/double(cur->N)+a*aprt(2*log(double(v->N))/cur->N);
            if(ucb>=max_ucb){
                max_ucb = ucb;
                best = cur;
            }
        }
    }
    else{
        for(int i=0;i<v->curChild;i++){
            State*cur = v->child[i];
            double ucb =1-double(cur->Q)/double(cur->N)+a*aprt(2*log(double(v->N))/cur->N);
            if(ucb>=max_ucb){
                max_ucb = ucb;
                best = cur;
            }
        }
    }
    return best;
}
State* TreePolicy(State*v0){
    while(win(v0.b) == 0){
        if(v0->childNum>v0->curChild)
            return Expand(v0);
        else{
            v0 =BestChild(v0,1/sqrt(2));
        }
    }
    return v0;
}
int DefaultPolicy(State*v,int deep,int cl){
    if(deep ==0)
    {
        return ;
    }
    int flag =0;
    srand((unsigned)time(NULL));
    int id=rand()%(v->childSet.size())+0;
    set<int>::iterator it;
    int flag =0;
    int childID;
    for(it=v->childSet.begin();it!=v->childSet.end();it++){
        if(flag == id){
            childID = *it;
        }
        else
            flag++;
    }
    int m = childID/11;
    int n = childID%11;
    v->b[m][n] = cl+1;
    v->childSet.erase(childID);
    int value =DefaultPolicy(v,deep-1,(!cl));
    v->b[m][n] = 0;
    v->childSet.insert(childID);
    return value;
}
void BackUp(State*v, int value){
    while(v!=NULL){
        v.N++;
        v.Q += value;
        v = v->father;
    }
}

int main()
{

    State *root =new State();
    root->father = NULL;
    root->c = color;
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            root->b[i][j] = board[i][j];
            if(board[i][j]==0)
            {
                root->childNum++;
                root->childSet.insert(i*11+j);
            }
        }
    }

    while(1){
        int deep;
        State* v =TreePolicy(root);
        int quality = DefaultPolicy(v,deep,v->c);
        BackUp(v, quality);
    }
    return 0;


}


/*
#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include<queue>
#include<cstring>
//#include "define.h"
#define MAX 121
#define color 1
#define MAX_FLOW 99
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

void printGraph(HeadNode *G) {
    ofstream mycout("test.txt",ios::app);
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
}
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
    if(u==122 || dist == 0)
        return dist;
    int  flow= 0;
    Node*node =G[u].link;
    while(node!=NULL){
        if((depth[node->adjvex]==depth[u]+1)&&(node->weight!=0))
        {
            int di = dfs(node->adjvex,dist < node->weight ? dist:node->weight);
            if(di>0)
            {
                node->weight = node->weight - di;
                update(node->adjvex,u,di);//反向边加权重
                flow +=di;
                dist -= di;
                if(dist == 0)
                    break;
            }
        }
        node = node->next;
    }
    return flow;
}
int Dinic(){
    int ans = 0;
    while(bfs()){
            ans+= dfs(0,MAX_FLOW) ;
            printGraph(G);
    }
    return ans;
}
int main()
{
    G =new HeadNode[MAX+2];
    for (int i=0;i<MAX+2;i++){
        G[i].nodeName = i;
        G[i].inDegree = 0;
        G[i].link = NULL;
    }
    for(int i=0;i<11;i++){
        if(color == 0){
            Node *n1 =new Node;
            n1->adjvex = i+1;
            n1->weight =MAX_FLOW;
            G[i+1].inDegree++;
            n1->next =G[0].link;
            G[0].link = n1;

            Node *n2 = new Node;
            n2->adjvex = 122;
            n2->weight = MAX_FLOW;
            G[122].inDegree++;
            n2->next = G[111+i].link;
            G[111+i].link=n2;
        }
        else{
            Node *n3 =new Node;
            n3->adjvex = 11*i + 1;
            n3->weight =MAX_FLOW;
            G[11*i+1].inDegree++;
            n3->next =G[0].link;
            G[0].link = n3;

            Node *n4 = new Node;
            n4->adjvex = 122;
            n4->weight = MAX_FLOW;
            G[122].inDegree++;
            n4->next = G[11*i+11].link;
            G[11*i+11].link=n4;
        }
    }
    for(int i = 0;i<11;i++){
        for(int j = 0;j<11;j++){
            if(board[i][j] == 0){
                find_next(i,j);
                int id = i*11+j+1;
                set<int>::iterator it;
                for(it=total.begin();it!=total.end();it++){
                    Node *node = new Node;
                    node->adjvex = *it;
                    node->weight = 1;
                    G[*it].inDegree++;
                    node->next = G[id].link;
                    G[id].link = node;
                }
                total.clear();
            }
        }
    }
    //printGraph(G);
    int flow =Dinic();
    cout<<flow<<endl;
    return 0;
}
*/
#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include<queue>
#include<cstring>
//#include "define.h"
#define MAX 121
#define color 1
#define MAX_FLOW 999
using namespace std;
int board[11][11] = {0};
int b[13][13]={0};
set<int> total;
int depth[MAX+2];
int visit[13][13];
void find_node(int i,int j,int c){
    if(i<0||i>=11||j<0||j>=11)
        return ;
    if(board[i][j] == (!c)+1)
        return ;
    if(board[i][j] == 0)
        total.insert(i*11+j+1);
    if(board[i][j] == 1){
        find_node(i+1,j,c);
        find_node(i,j+1,c);
        find_node(i+1,j-1,c);
        if(i==10)
            total.insert(122);
    }
    if(board[i][j] == 2){
        find_node(i,j+1,c);
        find_node(i+1,j,c);
        find_node(i-1,j+1,c);
        if(j==10)
            total.insert(122);
    }
}
void find_next(int i, int j,int c){
    if(c == 1)
    {
        find_node(i+1,j,1);
        find_node(i,j+1,1);
        find_node(i-1,j+1,1);
    }
    else
    {
        find_node(i,j+1,0);
        find_node(i+1,j,0);
        find_node(i+1,j-1,0);

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
ofstream mycout("test.txt",ios::app);
void printGraph(HeadNode *G) {
    ofstream mycout("test.txt",ios::app);
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
}
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
int bfs(HeadNode*G){

    queue<int> Q;
    while (!Q.empty())
        Q.pop();
    memset(depth,0,sizeof(depth));

    depth[0] = 1;
    Q.push(0);
    while(!Q.empty()){

        int u =Q.front();

        Q.pop();

        if(u ==122){
            return 1;
        }

        Node*node =G[u].link;

        while(node !=NULL)
        {
            if((depth[node->adjvex]==0)&&(node->weight>0))
            {

                depth[node->adjvex] = depth[u] + 1;
                Q.push(node->adjvex);
            }
            node =node->next;
        }
    }
    if(depth[122]>0)
        return 1;
    return 0;
}
//如果(v,u)已经存在，则增加权重，否则增加一条边
void update(int v,int u,int d,HeadNode*G){
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
int dfs(int u,int dist,HeadNode*G){
    if(u==122 || dist == 0)
        return dist;
    int  flow= 0;
    Node*node =G[u].link;
    while(node!=NULL){
        if((depth[node->adjvex]==depth[u]+1)&&(node->weight!=0))
        {
            int di = dfs(node->adjvex,dist < node->weight ? dist:node->weight,G);
            if(di>0)
            {
                node->weight = node->weight - di;
                update(node->adjvex,u,di,G);//反向边加权重
                flow +=di;
                dist -= di;
                if(dist == 0)
                    break;
            }
        }
        node = node->next;
    }
    return flow;
}
int Dinic(HeadNode*G){
    int ans = 0;
    while(bfs(G)){
            int di= dfs(0,MAX_FLOW,G) ;
            ans+=di;
    }
    return ans;
}
void find_ne(int i,int j ,int c ){

    if(i<0||j<0||i>12||j>12)
        return ;
    if(b[i][j]==3||b[i][j]==(!c)+1)
        return;
    if(visit[i][j] ==1){
        return;
    }
    else{
        visit[i][j]=1;
        if(b[i][j]==0)
            total.insert(i*11+j-11);
        else
        {
            find_ne(i-1,j,c);
            find_ne(i+1,j,c);
            find_ne(i,j+1,c);
            find_ne(i,j-1,c);
            find_ne(i-1,j+1,c);
            find_ne(i+1,j-1,c);
        }

    }


}
void find_neighbor(int i, int j,int c)
{
    visit[i][j] =1;

    find_ne(i-1,j,c);
    find_ne(i+1,j,c);
    find_ne(i,j+1,c);
    find_ne(i,j-1,c);
    find_ne(i-1,j+1,c);
    find_ne(i+1,j-1,c);
}
int get_s(HeadNode*graph, int u, int t[]){
    int first=MAX_FLOW;
    int second=MAX_FLOW;
    Node *n =graph[u].link;

    while(n !=NULL){
        if(t[n->adjvex] < first){
            second =first;
            first = t[n->adjvex];
        }
        else if(t[n->adjvex] < second){
            second = t[n->adjvex];
        }
        n= n->next;
    }

    return second;
}
void createGragh(HeadNode*G, int c)
{

    for (int i=0;i<MAX+2;i++){
        G[i].nodeName = i;
        G[i].inDegree = 0;
        G[i].link = NULL;
    }
    if(c==0){
        for(int i=0;i<11;i++){
            if(board[0][i]==1)
                find_next(0,i,0);
            else if(board[0][i]==0)
                total.insert(i+1);
            if(board[10][i]==0){
                Node *n2 = new Node;
                n2->adjvex = 122;
                n2->weight = MAX_FLOW;
                G[122].inDegree++;
                n2->next = G[111+i].link;
                G[111+i].link=n2;
            }
        }
        set<int>::iterator it;
        for(it=total.begin();it!=total.end();it++){
            Node *node = new Node;
            node->adjvex = *it;
            node->weight = MAX_FLOW;
            G[*it].inDegree++;
            node->next = G[0].link;
            G[0].link = node;
        }
        total.clear();
    }
    else{
        for(int i=0;i<11;i++){
            if(board[i][0]==2)
                find_next(i,0,1);
            else if(board[i][0]==0)
                total.insert(i*11+1);
            if(board[i][10]==0){
                Node *n4 = new Node;
                n4->adjvex = 122;
                n4->weight = MAX_FLOW;
                G[122].inDegree++;
                n4->next = G[11*i+11].link;
                G[11*i+11].link=n4;
            }
        }
        set<int>::iterator it;
        for(it=total.begin();it!=total.end();it++){
            Node *node = new Node;
            node->adjvex = *it;
            node->weight = MAX_FLOW;
            G[*it].inDegree++;
            node->next = G[0].link;
            G[0].link = node;
        }
        total.clear();
    }
    /*
    for(int i=0;i<11;i++){
        if(c == 0){
            if(board[0][i]==1){
                find_next(0,i,0);
                set<int>::iterator it;
                for(it=total.begin();it!=total.end();it++){
                    Node *node = new Node;
                    node->adjvex = *it;
                    node->weight = MAX_FLOW;
                    G[*it].inDegree++;
                    node->next = G[0].link;
                    G[0].link = node;
                }
                total.clear();
            }
            else if(board[0][i]==0){
                Node *n1 =new Node;
                n1->adjvex = i+1;
                n1->weight =MAX_FLOW;
                G[i+1].inDegree++;
                n1->next =G[0].link;
                G[0].link = n1;
            }
            if(board[10][i]==0){
                Node *n2 = new Node;
                n2->adjvex = 122;
                n2->weight = MAX_FLOW;
                G[122].inDegree++;
                n2->next = G[111+i].link;
                G[111+i].link=n2;
            }
        }
        else{
            if(board[i][0]==2){
                find_next(0,i,0);
                set<int>::iterator it;
                for(it=total.begin();it!=total.end();it++){
                    Node *node = new Node;
                    node->adjvex = *it;
                    node->weight = MAX_FLOW;
                    G[*it].inDegree++;
                    node->next = G[0].link;
                    G[0].link = node;
                }
                total.clear();

            }
            else if(board[i][0] ==0){
                Node *n3 =new Node;
                n3->adjvex = 11*i + 1;
                n3->weight =MAX_FLOW;
                G[11*i+1].inDegree++;
                n3->next =G[0].link;
                G[0].link = n3;
            }
            if(board[i][10]==0){
                Node *n4 = new Node;
                n4->adjvex = 122;
                n4->weight = MAX_FLOW;
                G[122].inDegree++;
                n4->next = G[11*i+11].link;
                G[11*i+11].link=n4;
            }
        }
    }*/

    for(int i = 0;i<11;i++){
        for(int j = 0;j<11;j++){
            if(board[i][j] == 0){
                find_next(i,j,c);
                int id = i*11+j+1;
                set<int>::iterator it;
                for(it=total.begin();it!=total.end();it++){
                    Node *node = new Node;
                    node->adjvex = *it;
                    if(*it==122)
                        node->weight=MAX_FLOW;
                    else
                        node->weight = 1;
                    G[*it].inDegree++;
                    node->next = G[id].link;
                    G[id].link = node;
                }
                total.clear();
            }
        }
    }
}
int main()
{
/*
    G =new HeadNode[MAX+2];
    for (int i=0;i<MAX+2;i++){
        G[i].nodeName = i;
        G[i].inDegree = 0;
        G[i].link = NULL;
    }
    for(int i=0;i<11;i++){
        if(color == 0){
            Node *n1 =new Node;
            n1->adjvex = i+1;
            n1->weight =MAX_FLOW;
            G[i+1].inDegree++;
            n1->next =G[0].link;
            G[0].link = n1;

            Node *n2 = new Node;
            n2->adjvex = 122;
            n2->weight = MAX_FLOW;
            G[122].inDegree++;
            n2->next = G[111+i].link;
            G[111+i].link=n2;
        }
        else{
            Node *n3 =new Node;
            n3->adjvex = 11*i + 1;
            n3->weight =MAX_FLOW;
            G[11*i+1].inDegree++;
            n3->next =G[0].link;
            G[0].link = n3;

            Node *n4 = new Node;
            n4->adjvex = 122;
            n4->weight = MAX_FLOW;
            G[122].inDegree++;
            n4->next = G[11*i+11].link;
            G[11*i+11].link=n4;
        }
    }

    for(int i = 0;i<11;i++){
        for(int j = 0;j<11;j++){
            if(board[i][j] == 0){
                find_next(i,j);
                int id = i*11+j+1;
                set<int>::iterator it;
                for(it=total.begin();it!=total.end();it++){
                    Node *node = new Node;
                    node->adjvex = *it;
                    node->weight = 1;
                    G[*it].inDegree++;
                    node->next = G[id].link;
                    G[id].link = node;
                }
                total.clear();
            }
        }
    }
    printGraph(G);
/*
    board[0][0] = 1;
    board[1][0] = 1;
    board[2][0] = 1;
    board[3][0] = 1;
    board[4][0] = 1;
    board[5][0] = 1;
    board[6][0] = 1;
    board[7][0] = 1;
    board[8][0] = 1;
    board[9][0] = 1;
   // board[10][0] = 1;
    HeadNode *G1 =new HeadNode[MAX+2];
    createGragh(G1,0);
    printGraph(G1);
    int flow =Dinic(G1);
    cout<<flow<<endl;
    freeGraph(G1);

*/
    board[0][10] =1;

    b[0][0]=3;
    b[0][12]=3;
    b[12][0]=3;
    b[12][12]=3;
    for(int i=1;i<12;i++){
        b[0][i]= 1;
        b[12][i] =1;
        b[i][0] = 2;
        b[i][12] = 2;
    }

    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            b[i+1][j+1] = board[i][j];
        }
    }

    HeadNode*G2=new HeadNode[MAX+2];
    HeadNode*G3 =new HeadNode[MAX+2];
    for (int i=0;i<MAX+2;i++){
        G2[i].nodeName = i;
        G2[i].inDegree = 0;
        G2[i].link = NULL;
        G3[i].nodeName = i;
        G3[i].inDegree = 0;
        G3[i].link = NULL;
    }
    set<int> sum;

    for(int i =1;i<12;i++)
    {
        for(int j=1;j<12;j++){
            if(b[i][j] ==0)
            {
                int id = i*11+j-11;
                sum.insert(id);
                //红子邻居图
                memset(visit,0,sizeof(visit));
                find_neighbor(i,j,0);
                set<int>::iterator it;
                for(it =total.begin();it!=total.end();it++){
                    Node*node = new Node;
                    node->adjvex = *it;
                    node->weight = 1;
                    G2[*it].inDegree++;
                    node->next = G2[id].link;
                    G2[id].link = node;
                }
                 total.clear();
                 //蓝子邻居图
                memset(visit,0,sizeof(visit));
                find_neighbor(i,j,1);
                for(it =total.begin();it!=total.end();it++){
                    Node*node = new Node;
                    node->adjvex = *it;
                    node->weight = 1;
                    G3[*it].inDegree++;
                    node->next = G3[id].link;
                    G3[id].link = node;
                }
                 total.clear();

            }
        }
    }

    int t_d[MAX+1];
    int t_d1[MAX+1];
    int p1[MAX+1];//红子潜力
    int p2[MAX+1];//蓝子潜力
    for(int i=0;i<MAX+1;i++){
        t_d[i] = MAX_FLOW;
        t_d1[i] =MAX_FLOW;
        p1[i] =MAX_FLOW;
        p2[i] =MAX_FLOW;
    }
    //计算红色潜力值
    for(int i=1;i<12;i++){
        if(b[1][i]==0){
            t_d[i] = 1;
        }
        if(b[11][i]==0){
            t_d1[110+i]=1;
        }
    }

    int flag;
    do{
        flag = 0;
         set<int>::iterator it;
         for(it = sum.begin();it!=sum.end();it++){
            int second =get_s(G2,*it,t_d);

            if(second<t_d[*it]-1){
                flag = 1;
                t_d[*it] = second+1;
            }
        }
    }while(flag);

    do{
        flag = 0;
         set<int>::iterator it;
         for(it = sum.begin();it!=sum.end();it++){

            int second =get_s(G2,*it,t_d1);
            if(second<t_d1[*it]-1){
                flag = 1;
                t_d1[*it] = second+1;
            }
        }
    }while(flag);
    for(int i = 0;i < MAX+1;i++){
        if(t_d[i]+t_d1[i]>=MAX_FLOW)
            p1[i] = MAX_FLOW;
        else
            p1[i] =t_d[i]+t_d1[i];
    }

    for(int i =0;i<MAX+1;i++){
        cout<<t_d[i]<<" "<<t_d1[i]<<" "<<p1[i]<<endl;
    }
    freeGraph(G2);
    for(int i=0;i<MAX+1;i++){
        t_d[i] = MAX_FLOW;
        t_d1[i] =MAX_FLOW;
    }
    //计算蓝色潜力值
    for(int i=1;i<12;i++){
        if(b[i][1]==0){
            t_d[i*11-10] = 1;
        }
        if(b[i][11]==0){
            t_d1[11*i]=1;
        }
    }
    do{
        flag = 0;
         set<int>::iterator it;
         for(it = sum.begin();it!=sum.end();it++){
            int second =get_s(G3,*it,t_d);
            if(second<t_d[*it]-1){
                flag = 1;
                t_d[*it] = second+1;
            }
        }
    }while(flag);
    do{
        flag = 0;
         set<int>::iterator it;
         for(it = sum.begin();it!=sum.end();it++){
            int second =get_s(G3,*it,t_d1);
            if(second < t_d1[*it]-1){
                flag = 1;
                t_d1[*it] = second+1;
            }
        }
    }while(flag);
    for(int i = 0;i < MAX+1;i++){
        if(t_d[i]+t_d1[i]>=MAX_FLOW)
            p2[i] = MAX_FLOW;
        else
            p2[i] =t_d[i]+t_d1[i];
    }
    for(int i=1;i<12;i++)
    {
        for(int j= 1;j<12;j++){
            cout<<t_d1[i*11+j-11]<<" ";
        }
        cout<<endl;
    }

    freeGraph(G3);
    int p_r =MAX_FLOW;//红色方潜力最小值
    int p_b =MAX_FLOW;
    int a_r =0;
    int a_b =0;
    set<int>::iterator it;
    for(it=sum.begin();it!=sum.end();it++){

        if(p1[*it]==p_r)
            a_r++;
        if(p1[*it]<p_r)
        {
            p_r =p1[*it];
            a_r =1;
        }

        if(p2[*it]==p_r)
            a_b++;
        if(p2[*it]<p_b)
        {
            p_b =p2[*it];
            a_b =1;
        }
    }
    cout<<p_r<<"  "<<a_r<<endl;
    cout<<p_b<<"  "<<a_b<<endl;


    return 0;

}




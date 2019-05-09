#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<set>
#include<cstring>
#include<queue>
using namespace std;
#define RED 0
#define BLUE 1
#define MAX_VALUE 9999999
#define MAX 121
#define MAX_FLOW 999
#define MAX_DEEP 2
int board[11][11] = {0};
int b[13][13]={0};
int visit[13][13];
int depth[MAX+2];
char cmd[40];
char response[2];
int color = 0;
set<int> total;

//邻接链表
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
int win(){
    HeadNode*G1 =new HeadNode[MAX+2];
    HeadNode*G2 =new HeadNode[MAX+2];
    createGragh(G1,color);
    createGragh(G2,(!color));
    Node*f1 =G1[0].link;
    Node*f2 =G2[0].link;
    if(f1->adjvex==122||f2->adjvex==122)
        return 1;
    freeGraph(G1);
    freeGraph(G2);
    return 0;

}
//根据board建立co的邻接矩阵
void createMartic(int co)
{
    int c[MAX+2][MAX+2] = {0};//残存网络
    for(int i = 0;i<11;i++)
    {
        if(co == 0)
        {
            c[0][i+1] = MAX_FLOW;
            c[111+i][122]=MAX_FLOW;
        }
        else{
            c[0][11*i+1] = MAX_FLOW;
            c[11*i+11][122] = MAX_FLOW;
        }
    }
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<11;j++)
        {
            if(board[i][j] ==0)
            {
                find_next(i,j,co);
                int id = i*11+j+1;
                set<int>::iterator it;
                for(it = total.begin();it!=total.end();it++)
                    c[id][*it] = 1;
            }
            total.clear();

        }

    }

}

void get_move(char* cmd)
{
	int x,y;
	x = cmd[0] - 'A';
	y = cmd[1] - 'A';
	board[x][y] = (!color)+1;
}
void make_move(char* response)
{
    int x,y;
    x = response[0]-'A';
    y = response[1]-'A';
    board[x][y] = color+1;
}
void search_move(char* response);
int min_function(int deep,double alpha, double beta);
int max_function(int deep,double alpha,double beta);
int nextstep(int deep,int alpha,int beta,bool isMAXplayer);
int evaluate1();
int evaluate2();
int main()
{

	while(1)
	{
	    fflush(stdout);
		//Get command
		scanf("%s",cmd);
		//return name

		if(!strcmp(cmd,"start"))//建立新棋局
		{
			scanf("%s",cmd);//获取己方棋色
			fflush(stdin);
			for(int i=0;i<11;i++)
				for(int j=0;j<11;j++)
					board[i][j] = 0;
			//Red
			if(!strcmp(cmd,"red"))
			{
				color = RED;
				//生成第一手行棋
				response[0]='A'+5;
				response[1]='A'+5;
				make_move(response);
				printf("move %s\n",response );
				fflush(stdout);
			}
			else//Blue
			{
				color = BLUE;
			}
			continue;
		}

		//make move
		if(!strcmp(cmd,"move"))
		{
			scanf("%s",cmd);
			fflush(stdin);
			//处理对方行棋
			get_move(cmd);
			//搜索最高评分行棋
			search_move(response);
/*
			for(int i=0;i<11;i++){
                for(int j=0;j<11;j++){
                    if(board[i][j]==0)
                    {
                        response[0]=i+'A';
                        response[1]=j+'A';
                    }
                }
			}
			*/
			make_move(response);
			printf("move %s\n",response);
			fflush(stdout);
			continue;
		}
        if(!strcmp(cmd,"name?"))
		{
			fflush(stdin);
			printf("name ly\n");
			fflush(stdout);
			continue;
		}
		//exit
		if(!strcmp(cmd,"exit"))
		{
			fflush(stdin);
			exit(0);
		}
		//wrong command
		if(!strcmp(cmd,"wrong"))
		{
			fflush(stdin);
			continue;
		}
		//start
	}
   /*
	color =1;
	board[0][0] = 2;
    board[0][3] = 2;
	board[4][2] =1;
	board[5][5] =1;
	board[8][8]=1;

	search_move(response);
	cout<<response[0]<<" "<<response[1]<<endl;
	*/
	return 0;

}


void search_move(char* response){
    int best_value = -MAX_VALUE;
    int flag = 0;
    for(int i=0;i<11;i++){
       for(int j=0;j<11;j++){
            if(board[i][j]==0){
                board[i][j] = color + 1;
                //int value = min_function(MAX_DEEP,-MAX_VALUE,MAX_VALUE);
                int value = nextstep(MAX_DEEP,-MAX_VALUE,MAX_VALUE,false);
                board[i][j] = 0;
                if (value > best_value){
                    response[0] = i + 'A';
                    response[1] = j + 'A';
                    best_value = value;
                }
                if (value>=MAX_VALUE){
                    flag = 1;
                    break;
                }
            }
            }
            if(flag)
                break;
        }

}

int nextstep(int deep,int alpha,int beta,bool isMAXplayer){
    if(deep == 0){
        return evaluate2();
    }
    if(isMAXplayer){
        int flag =0;
        for(int i=0;i<11;i++){
            for(int j=0;j<11;j++){

               if(board[i][j]==0){
                    board[i][j] = color+1;
                    int value = nextstep(deep-1,alpha,beta,false);
                    board[i][j] = 0;
                    alpha = alpha>value?alpha:value;
                    if(alpha>=beta){
                        break;
                        flag=1;
                    }

                }
            }
            if(flag)
                break;
        }
        return alpha;
    }
    else{
        int flag =0;
        for(int i=0;i<11;i++){
            for(int j=0;j<11;j++){

               if(board[i][j]==0){
                    board[i][j] =(!color)+1;
                    int value = nextstep(deep-1,alpha,beta,false);
                    board[i][j] = 0;
                    alpha = beta<value?beta:value;
                    if(alpha>=beta){
                        break;
                        flag=1;
                    }

                }
            }
            if(flag)
                break;
        }
        return beta;
    }
}
//最大流
int evaluate1()
{

    int score1, score2;
    HeadNode *G1=new HeadNode[MAX+2];
    //HeadNode*G2=new HeadNode[MAX+2];//G2分别为玩家和对手的最大流图
    createGragh(G1,color);
    //createGragh(G2,(!color));
    score1 =Dinic(G1);
    //score2 =Dinic(G2);
    //freeGraph(G1);
    for(int i=0;i<MAX+2;i++)
    {
        Node*p1 =G1[i].link;
        Node*p2;
        while(p1!= NULL)
        {
            p2 = p1->next;
            delete p1;
            p1 = p2;
        }
    }
    delete[] G1;
    //freeGraph(G2);
    return score1;

    //return 1;
}
//双距离
int evaluate2(){
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
/*
    for(int i =0;i<MAX+1;i++){
        cout<<t_d[i]<<" "<<t_d1[i]<<" "<<p1[i]<<endl;
    }*/
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
    /*
    for(int i=1;i<12;i++)
    {
        for(int j= 1;j<12;j++){
            cout<<t_d1[i*11+j-11]<<" ";
        }
        cout<<endl;
    }
    */
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
    if(color==0){
        return a_r-p_r;
    }
    else
        return a_b-p_b;

}
int max_function(int deep,double alpha,double beta){
    if(deep == 0){
        return evaluate1();
    }
    int flag = 0;
    double best = - MAX_VALUE;
    for(int i = 0;i<11;i++){
        for (int j =0;j<11;j++){
            if(board[i][j]==0){
                board[i][j] = color + 1;
                double value = min_function(deep-1, alpha, best > beta ? best : beta);
                board[i][j] = 0;

                if(value>best)
                {
                    best = value;
                }
                if(value > alpha)
                {
                    flag = 1;
                    break;
                }
            }
        }
        if(flag)
            break;
    }
    return best;
}
int min_function(int deep,double alpha, double beta){
    if(deep == 0){
        return evaluate1();
    }
    int flag = 0;
    double best =  MAX_VALUE;
    for(int i = 0;i<11;i++){
        for (int j =0;j<11;j++){

            if(board[i][j]==0){
                board[i][j] = (!color) + 1;
                double value = max_function(deep-1, best < alpha ? best : alpha, beta);
                board[i][j] = 0;

                if(value>best)
                {
                    best = value;
                }
                if(value < beta)
                {
                    flag = 1;
                    break;
                }
            }
        }
        if(flag)
            break;
    }
    return best;
}

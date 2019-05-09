#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<set>
#include<cstring>
#include<queue>
#include<ctime>
#include<cmath>
using namespace std;
#define RED 0
#define BLUE 1
#define MAX_VALUE 999
#define MAX 121
#define MAX_FLOW 99
#define MAX_DEEP 0
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
int evaluate2(int now_b[][11],int c){
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
            b[i+1][j+1] = now_b[i][j];
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
    if(c==0){
        return (a_r-a_b)+100*(p_b-p_r);
    }
    else
        return (a_b-a_r)+100*(p_r-p_b);

}
void find_ne2(int i,int j ,int c ){

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
            find_ne2(i-1,j,c);
            find_ne2(i+1,j,c);
            find_ne2(i,j+1,c);
            find_ne2(i,j-1,c);
            find_ne2(i-1,j+1,c);
            find_ne2(i+1,j-1,c);
            if(c==0&&i==10)
                total.insert(-1);
            else if(c==1&&j==10)
                total.insert(-1);

        }

    }
}
void find_neighbor2(int i, int j,int c)
{
    visit[i][j] =1;

    find_ne2(i-1,j,c);
    find_ne2(i+1,j,c);
    find_ne2(i,j+1,c);
    find_ne2(i,j-1,c);
    find_ne2(i-1,j+1,c);
    find_ne2(i+1,j-1,c);
}
int win(int now_b[][11]){
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
            b[i+1][j+1] = now_b[i][j];
        }
    }
    for(int i =0 ;i<11;i++){
        if(now_b[i][0] == 2){
            find_neighbor2(i, 0 , 1);
            memset(visit,0,sizeof(visit));
            set<int>::iterator it;
            it =total.find(-1);
            if(it!=total.end())
            {
                total.clear();
                return 2;
            }
            total.clear();
        }
    }
    for(int j =0 ;j<11;j++){
        if(now_b[0][j] == 1){
            find_neighbor2(0, j , 0);
            memset(visit,0,sizeof(visit));
            set<int>::iterator it;
            it =total.find(-1);
            if(it!=total.end())
            {
                total.clear();
                return 2;
            }
            total.clear();
        }
    }
    return 0;

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

    int id=rand()%(v->childNum - v->curChild)+0;
    set<int>::iterator it;
    int flag =0;
    int childID;
    for(it=v->childSet.begin();it!=v->childSet.end();it++){
        if(flag == id){
            childID = *it;
        }
        flag++;
    }
    State *v1 =new State();
    v1->father = v;
    v1->c = (!v->c);
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            v1->b[i][j] = v->b[i][j];
            if(v->b[i][j] ==0)
                v1->childSet.insert(i*11+j);
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
            double ucb = double(cur->Q)/double(cur->N)+a*sqrt(2*log(double(v->N))/cur->N);
            if(ucb>=max_ucb){
                max_ucb = ucb;
                best = cur;
            }
        }
    }
    else{
        for(int i=0;i<v->curChild;i++){
            State*cur = v->child[i];
            double ucb =1-double(cur->Q)/double(cur->N)+a*sqrt(2*log(double(v->N))/cur->N);
            if(ucb>=max_ucb){
                max_ucb = ucb;
                best = cur;
            }
        }
    }
    return best;
}
State* TreePolicy(State*v0){
    while(win(v0->b) == 0){
        if(v0->childNum>v0->curChild)
            return Expand(v0);
        else{
            v0 =BestChild(v0,1/sqrt(2));
        }
    }
    return v0;
}
int DefaultPolicy(State*v,int deep,int cl){
    int winner = win(v->b);
    if(winner != 0){
        if(winner == (color+1))
            return 1;
        else
            return 0;
    }
    if(deep ==0)
    {
        int score1=evaluate2(v->b,color);
        int score2 =evaluate2(v->b,(!color));
        if(score1>=score2)
            return 1;
        else
            return 0;
    }

    int id=rand()%(v->childSet.size())+0;
    set<int>::iterator it;
    int flag =0;
    int childID;
    for(it=v->childSet.begin();it!=v->childSet.end();it++){
        if(flag == id){
            childID = *it;
        }
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
        v->N++;
        v->Q += value;
        v = v->father;
    }
}
void freeTree(State*root){
    queue<State*> Q;
    Q.push(root);
    while(Q.empty()){
        State*s =Q.front();
        Q.pop();
        for(int i=0;i<s->curChild;i++){
            Q.push(s->child[i]);
        }
        delete s;
    }
}
void UCT_search(char* response){
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
    int MAX_ITERATOR = 1000;
    int itor = 0;
    srand((unsigned)time(NULL));
    while(itor<MAX_ITERATOR){
        State* v =TreePolicy(root);
        int quality = DefaultPolicy(v,44,v->c);
        BackUp(v, quality);
        itor++;
    }
    State*best =BestChild(root,0);
    response[0] = best->line+'A';
    response[1] = best->row+'A';
    freeTree(root);
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
            UCT_search(response);
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



	return 0;
}

#include<iostream>
#include"define.h"
#include"search.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
double e_max(double x,double y){return x>y?x:y;}
double e_min(double x,double y){return x<y?x:y;}
double f1(double w)
{
	double temp;
	temp=(1.0)/(sqrt(w)+1.0);
	return temp;
}
double f2(double w)
{
	double temp;
	temp=(w*0.3)/(w+1.0);
	return temp;
}
double f3(double w)
{
	double temp;
	temp=(w*0.2)/(w+1.0);
	return temp;
}
double f4(double w)
{
	double temp;
	temp=(0.8)/(sqrt(w)+1.0);
	return temp;
}
extern int posx[8]={0,3,6,9,0,3,6,9};
extern int posy[8]={3,0,0,3,6,9,9,6};

int Board[10][10];//棋盘结构
bool ismove(int x,int y);
void creatMove(int color,stackType &moveList);
void creatMove2(int d,moveType m,stackType &moveList);
bool search_move( int color,moveType&goodMove);
double nextStep(int depth,double alpha,double beta,int color);
void calc_value(int c,int v[10][10],int mode);
double evaluate(int color);
void makeMove(moveType m,int &posnum);
void unmakeMove(moveType m,int &posnum);

int main(int argc, char *argv[])
{
	Step step;//临时步结构
	char message[256];//通信消息缓冲
    int computerSide;//己方执棋颜色
    int start=0;//对局开始标记

	//此处放置初始化代码
    //...

    //程序主循环
	while (1)
	{
		fflush(stdout);

        //获取平台消息
		scanf("%s", message);

        //分析命令
		if(strcmp(message,"move")==0)//行棋
		{
			scanf("%s", message);//获取对手行棋着法
            fflush(stdin);

			step.start.x=message[0]-'A';
			step.start.y=message[1]-'A';
			step.end.x=message[2]-'A';
			step.end.y=message[3]-'A';
            step.bar.x=message[4]-'A';
            step.bar.y=message[5]-'A';

            //处理对手行棋
            Board[step.start.x][step.start.y]=EMPTY;
            Board[step.end.x][step.end.y]=computerSide^1;
            Board[step.bar.x][step.bar.y]=BAR;
			for(int i=0;i<8;i++)
			{
				if(posx[i]==step.start.x&&posy[i]==step.start.y)
				{
					posx[i]=step.end.x;
					posy[i]=step.end.y;
				}
			}
            //...

			//生成着法，并保存在step结构中
            //...
            moveType m;
			search_move( computerSide,m);
			step.start.x=m.x[0];
			step.start.y=m.y[0];
			step.end.x=m.x[1];
			step.end.y=m.y[1];
			step.bar.x=m.x[2];
			step.bar.y=m.y[2];
            //处理己方行棋
            Board[step.start.x][step.start.y]=EMPTY;
            Board[step.end.x][step.end.y]=computerSide;
            Board[step.bar.x][step.bar.y]=BAR;
			for(int j=0;j<8;j++)
			{
				if(posx[j]==step.start.x&&posy[j]==step.start.y)
				{
					posx[j]=step.end.x;
					posy[j]=step.end.y;
				}
			}
            //...

            //输出着法
			printf("move %c%c%c%c%c%c\n",step.start.x+'A',step.start.y+'A',step.end.x+'A',step.end.y+'A',step.bar.x+'A',step.bar.y+'A');
		}
		else if(strcmp(message,"new")==0)//建立新棋局
		{
            int i,j;

			scanf("%s",message);//获取己方执棋颜色
            fflush(stdin);

			if(strcmp(message,"black")==0)//执黑
				computerSide=BLACK;
			else//执白
				computerSide=WHITE;

            //初始化棋局
            for(i=0;i<10;++i)
                for(j=0;j<10;++j)
                    Board[i][j]=EMPTY;
            Board[0][3]=Board[3][0]=Board[6][0]=Board[9][3]=WHITE;
            Board[0][6]=Board[3][9]=Board[6][9]=Board[9][6]=BLACK;
            //...

            start=1;

            if(computerSide==BLACK)
            {
                //生成第一手着法，并保存在step结构中
                //...
			/*	moveType m;
				search_move( computerSide,m);
				step.start.x=m.x[0];
				step.start.y=m.y[0];
				step.end.x=m.x[1];
				step.end.y=m.y[1];
				step.bar.x=m.x[2];
				step.bar.y=m.y[2];
                //处理己方行棋
                Board[step.start.x][step.start.y]=EMPTY;
                Board[step.end.x][step.end.y]=computerSide;
                Board[step.bar.x][step.bar.y]=BAR;
				for(int k=0;k<8;k++)
				{
				if(posx[k]==step.start.x&&posy[k]==step.start.y)
				{
					posx[k]=step.end.x;
					posy[k]=step.end.y;
				}
				}
                //...

                //输出着法*/
				step.start.x=0;
				step.start.y=6;
				step.end.x=8;
				step.end.y=6;
				step.bar.x=4;
				step.bar.y=6;
				posx[4]=8;
				posx[4]=6;
                printf("move %c%c%c%c%c%c\n",step.start.x+'A',step.start.y+'A',step.end.x+'A',step.end.y+'A',step.bar.x+'A',step.bar.y+'A');
            }
		}
        else if (strcmp(message, "error") == 0)//着法错误
        {
            fflush(stdin);

            //...
        }
		else if (strcmp(message, "name?") == 0)//询问引擎名
		{
            fflush(stdin);

            //输出引擎名
			printf("name ly\n");
		}
		else if (strcmp(message, "end") == 0)//对局结束
		{
            fflush(stdin);

			start = 0;
            //...
		}
		else if (strcmp(message, "quit") == 0)//退出引擎
		{
            fflush(stdin);

            //...
			printf("Quit!\n");
			break;
		}
	}
	return 0;
}
int dt[2][8]={{-1,-1,0,1,1,1,0,-1},{0,-1,-1,-1,0,1,1,1}};
bool ismove(int x,int y){
	return x>=0&&y>=0&&x<10&&y<10&&Board[x][y]==EMPTY;
}
void creatMove(int color,stackType &moveList){
	moveType m;
	int k=0;
	if(color==BLACK)
		k=4;
	for(int i=k;i<k+4;i++)
	{
		m.x[0]=posx[i];
		m.y[0]=posy[i];
		Board[m.x[0]][m.y[0]]=EMPTY;//障碍可以放在原棋子处
		creatMove2(1,m,moveList);
		Board[m.x[0]][m.y[0]]=color;
	}
}
void creatMove2(int d,moveType m,stackType &moveList)
{
	if(d==3)
		moveList.push(m);
	else{
		for(int i=0;i<8;i++){
			int t=1;
			m.x[d]=m.x[d-1]+t*dt[0][i];
			m.y[d]=m.y[d-1]+t*dt[1][i];
			while(ismove(m.x[d],m.y[d]))
			{
				creatMove2(d+1,m,moveList);
				++t;
				m.x[d]=m.x[d-1]+t*dt[0][i];
				m.y[d]=m.y[d-1]+t*dt[1][i];
			}
		}
	}
}
bool search_move( int color,moveType&goodMove)
{
	moveType m;
	int posnum;
	stackType moveList;
	double value;
	double bestValue;
	creatMove(color,moveList);
	for(int i=0;i<moveList.num;i++)
	{
		m=moveList.move[i];
		makeMove(m,posnum);
		if(moveList.num<200)
			value=-nextStep(MAX_DEEP+1,-MAX_VALUE,MAX_VALUE,color^1);
		else
			value=-nextStep(MAX_DEEP,-MAX_VALUE,MAX_VALUE,color^1);
		unmakeMove(m,posnum);
		if(value>=bestValue)
		{
			goodMove=moveList.move[i];
			bestValue=value;
		}
		if(bestValue>=MAX_VALUE)
			break;
	}

	return 1;
}
double nextStep(int depth,double alpha,double beta,int color)
{
	stackType moveList;
	moveType m;
	int posnum;
	double value,goodValue;
	creatMove(color,moveList);
	if(moveList.num==0||depth<=0)
		return evaluate(color);
	m = moveList.move[0];
	makeMove(m,posnum);
	goodValue=-nextStep(depth-1,-beta,-alpha,color^1);
	unmakeMove(m,posnum );
	for(int i=1;i<moveList.num;i++)
	{
		if(goodValue<beta)
		{
			if(goodValue>alpha)
			{
				alpha=goodValue;
				m = moveList.move[i];
				makeMove(m,posnum);
				value = -nextStep (depth-1 , -alpha-1 , -alpha , color^1);
				if(value>alpha && value<beta)
					goodValue=-nextStep(depth-1,-beta,-value,color^1);
				else if(value>goodValue)
					goodValue=value;
				unmakeMove(m,posnum);
			}
		}
		else
			break;
	}
	return goodValue;
}

const int inf = 0xfffffff;
const double EQUAL = 0.2;

int p[10][10],r_value[10][10],w_value[10][10],f_value[10][10];
bird_queue Q;
void calc_value(int c,int v[10][10],int mode)
{
	int i,k,p;
	int xf,yf,tx,ty,nx,ny;
	bool vis[10][10];

	if (c == WHITE) p = 0;
	else p = 4;

	for (k=0;k<4;++k) {
		xf = posx[p+k];
		yf = posy[p+k];
		memset(vis,0,sizeof(vis));
		vis[xf][yf] = 1;
		v[xf][yf] = 0;
		Q.push(xf,yf);
		while(!Q.empty()) {
			tx = Q.front().x;
			ty = Q.front().y;
			Q.pop();
			for (i = 0;i<8;++i) {
				nx = tx + dt[0][i];
				ny = ty + dt[1][i];
				while( ismove(nx,ny) ) {
					if (vis[nx][ny] == 0) {
						vis[nx][ny] = 1;
						if (v[nx][ny] > v[tx][ty] + 1)
							v[nx][ny] = v[tx][ty] + 1;
						Q.push(nx,ny);
					}
					if (mode == KVALUE)
						break;
					nx += dt[0][i];
					ny += dt[1][i];
				}
			}
		}
	}
	return;
}

double evaluate(int color)
{
	int i,j,k,f_cnt;

	double t1,t2,c1,c2,w,t,m,alph_r,alph_w;
	t1 = t2 = c1 = c2 = w = t = m = alph_r = alph_w = 0;
	for (i=0;i<10;++i)
		for (j=0;j<10;++j)
			r_value[i][j] = w_value[i][j] = inf;
	calc_value(BLACK,r_value,QVALUE);
	calc_value(WHITE,w_value,QVALUE);

	for (i=0;i<10;++i)
	for (j=0;j<10;++j)
		if(r_value[i][j]==w_value[i][j])
			if(r_value[i][j]==inf)continue;
			else 	t1+=EQUAL;
		else
			if (r_value[i][j]<=w_value[i][j])t1+=1;
			else t1+=-1;
	for (i=0;i<10;++i)
	for (j=0;j<10;++j)
		if(r_value[i][j]==w_value[i][j])continue;
		else
			if(r_value[i][j]==inf)		c1+= -pow(2.0,-w_value[i][j]);
			else if(w_value[i][j]==inf)	c1+=  pow(2.0,-r_value[i][j]);
				 else c1+=pow(2.0,-r_value[i][j])-pow(2.0,-w_value[i][j]);
	for (i=0;i<10;++i)
	for (j=0;j<10;++j)
	 w+=pow(0.5,abs(r_value[i][j]-w_value[i][j]));
	calc_value(BLACK,r_value,KVALUE);
	calc_value(WHITE,w_value,KVALUE);
	for (i=0;i<10;++i)
	for (j=0;j<10;++j)
		if(r_value[i][j]==w_value[i][j])
			if(r_value[i][j]==inf)continue;
			else 	t2+=EQUAL;
		else
			if (r_value[i][j]<=w_value[i][j])t2+=1;
			else t2+=-1;
	for (i=0;i<10;++i)
	for (j=0;j<10;++j)
		c2+=e_min(1.0,e_max(-1.0,(double)(w_value[i][j]-r_value[i][j])/6.0));
	for(i=0;i<10;i++)
	for(j=0;j<10;j++)
	{
		if(Board[i][j]!=EMPTY)continue;
		f_cnt=0;
		for(k=0;k<8;k++)
			{
				if(Board[i+dt[0][k]][j+dt[1][k]]==EMPTY)
				++f_cnt;
			}
		f_value[i][j]=f_cnt;
	}

	for(i=0;i<10;i++)
	for(j=0;j<10;j++)
	{
		if(r_value[i][j]==inf||r_value[i][j]==0);
		else alph_r+=pow(0.5,r_value[i][j])*f_value[i][j];
		if(w_value[i][j]==inf||w_value[i][j]==0);
		else alph_w+=pow(0.5,w_value[i][j])*f_value[i][j];
	}
	w-=40;
	t = t1*f1(w)
	  + c1*f2(w)
	  + t2*f3(w)
	  +	c2*f4(w);
	m=(w*w)/(1.0+alph_w)-(w*w)/(1.0+alph_r);
return t+m;
	m=(w*w)/(1.0+alph_w)-(w*w)/(1.0+alph_r);
return t+m;
}
void makeMove(moveType m,int &posnum)
{
	Board[m.x[1]][m.y[1]]=Board[m.x[0]][m.y[0]];
	Board[m.x[0]][m.y[0]]=EMPTY;
	Board[m.x[2]][m.y[2]]=BAR;
	for(int i=0;i<8;i++){
		if(posx[i]==m.x[0]&&posy[i]==m.y[0]){
			posx[i]=m.x[1];
			posy[i]=m.y[1];
			posnum=i;
			break;
		}
	}
}
void unmakeMove(moveType m,int &posnum)
{
	Board[m.x[2]][m.y[2]]=EMPTY;
	Board[m.x[0]][m.y[0]]=Board[m.x[1]][m.y[1]];
	Board[m.x[1]][m.y[1]]=EMPTY;
	posx[posnum]=m.x[0];
	posy[posnum]=m.y[0];
}
void stackType::push(moveType m){
	move[num]=m;
	num++;
}
void stackType::pop(){
	num--;
}
moveType stackType::getTop(){
	return move[num];
}


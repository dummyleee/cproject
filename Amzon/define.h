#include<math.h>
#define  MAXMOVE    3000    //һ����ֵ�����з�����
#define BLACK 0
#define WHITE 1
#define EMPTY 2
#define BAR 3
#define MAX_DEEP 2
#define MAX_VALUE 9999999 
struct moveType {
	int x[3];                 //x[0] �������x�����ꡢx[1]�������x�����ꡢx[2]�ϰ�����
    int y[3];                 //y[0] �������y�����ꡢy[1]�������y�����ꡢy[2]�ϰ�����
};

extern    int posx[8];                          
extern    int posy[8];


typedef struct _Point{ //��ṹ
	int x,y;
}Point;

typedef struct _Step{ //���ṹ
	Point start,end,bar;
	int value;
}Step;

const int Q_AMT = 10000; 
const int KVALUE = 1;
const int QVALUE = 0;
struct stackType{
	moveType move[MAXMOVE];
	int num;
	stackType(){num=0;}
	void push(moveType m);
	void pop();
	moveType getTop();
};
struct bird_point 
{
	int x,y,w;
};
class  bird_queue
{
private:
	int t,f;
	struct bird_point q[Q_AMT];
public:
	 bird_queue() { t = 0;f = 0; }
	void push(int x,int y){
		q[f].x = x;
		q[f++].y = y;
		if (f >= Q_AMT) f = 0;
	}
	bool empty(){
		if (t == f) return true;
		else return false;
	}
	void pop(){ t++; if (t >= Q_AMT) t = 0; }
	bird_point front(){ return q[t]; }
};
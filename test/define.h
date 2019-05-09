#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#define MAX 121
typedef struct _ENode
{
    int ivex;                   // 该边所指向的顶点的位置
    struct _ENode *next_edge;   // 指向下一条弧的指针
}ENode, *PENode;

// 邻接表中表的顶点
typedef struct _VNode
{
    char data;              // 顶点信息
    ENode *first_edge;      // 指向第一条依附该顶点的弧
}VNode;

// 邻接表
typedef struct _LGraph
{
    int vexnum;             // 图的顶点的数目
    int edgnum;             // 图的边的数目
    VNode vexs[MAX];
}LGraph;


#endif // DEFINE_H_INCLUDED

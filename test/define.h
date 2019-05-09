#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#define MAX 121
typedef struct _ENode
{
    int ivex;                   // �ñ���ָ��Ķ����λ��
    struct _ENode *next_edge;   // ָ����һ������ָ��
}ENode, *PENode;

// �ڽӱ��б�Ķ���
typedef struct _VNode
{
    char data;              // ������Ϣ
    ENode *first_edge;      // ָ���һ�������ö���Ļ�
}VNode;

// �ڽӱ�
typedef struct _LGraph
{
    int vexnum;             // ͼ�Ķ������Ŀ
    int edgnum;             // ͼ�ıߵ���Ŀ
    VNode vexs[MAX];
}LGraph;


#endif // DEFINE_H_INCLUDED

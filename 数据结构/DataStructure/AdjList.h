// 本数据结构仅为完成作业，泛用性很差！！！
#ifndef _ADJLIST_H_
#define _ADJLIST_H_
#include <iostream>
using namespace std;
#define MAXSIZE 100
#define MAXINT 32767
// 定义邻接表的节点
struct AdjListNode
{
    int index;
    int weight;
    AdjListNode *next = nullptr;
};
//定义邻接表的头结点
//这里我们默认下标就是点的编号
struct AdjListHead
{
    int num = 0;
    AdjListNode *next = nullptr;
};
//创建邻接表
//有向图
AdjListHead* CreateAdjList()
{
    cout << "请输入顶点数和边数：" << endl;
    int vexnum, arcnum;
    cin >> vexnum >> arcnum;
    AdjListHead *adjListHead = new AdjListHead[vexnum];
    for (int i = 0; i < arcnum; i++)
    {
        cout << "请输入边的起点、终点和权重：" << endl;
        int index1, index2, weight;
        cin >> index1 >> index2 >> weight;
        AdjListNode *adjListNode = new AdjListNode;
        adjListNode->index = index2;
        adjListNode->weight = weight;
        adjListNode->next = adjListHead[index1].next;
        adjListHead[index1].next = adjListNode;
        adjListHead[index1].num++;
    }
    return adjListHead;
}
// 对邻接表进行深度优先遍历
//调用本函数请先将visited数组初始化为0
void DFSAdjList(AdjListHead *adjListHead, int index, int visited[])
{
    cout << index << " ";
    visited[index] = 1;
    AdjListNode *adjListNode = adjListHead[index].next;
    while (adjListNode)
    {
        if (!visited[adjListNode->index])
            DFSAdjList(adjListHead, adjListNode->index, visited);
        adjListNode = adjListNode->next;
    }
    return;
}
// 对邻接表进行广度优先遍历
//调用本函数请先将visited数组初始化为0
void BFSAdjList(AdjListHead *adjListHead, int index, int visited[])
{
    int queue[MAXSIZE];
    int front = 0, rear = 0;
    queue[rear++] = index;
    visited[index] = 1;
    while (front != rear)
    {
        int temp = queue[front++];
        cout << temp << " ";
        AdjListNode *adjListNode = adjListHead[temp].next;
        while (adjListNode)
        {
            if (!visited[adjListNode->index])
            {
                queue[rear++] = adjListNode->index;
                visited[adjListNode->index] = 1;
            }
            adjListNode = adjListNode->next;
        }
    }
    return;
}
#endif
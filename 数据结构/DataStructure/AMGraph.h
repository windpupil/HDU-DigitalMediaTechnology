//本数据结构仅为完成作业，泛用性很差！！！
#ifndef _AMGRAPH_H_
#define _AMGRAPH_H_
#include <iostream>
using namespace std;
#define MAXSIZE 100
#define MAXINT 32767
// 定义顶点的数据类型
template <typename T>
struct VexNode
{
    // T data;//以后需要什么顶点内容可以写成一个struct，然后用VexNode（struct）来定义顶点
    int index; // 顶点编号
};
template <typename T>
// 定义邻接矩阵
struct AMGraph // Adjacency Matrix Graph
{
    VexNode<T> vexs[MAXSIZE];
    int arcs[MAXSIZE][MAXSIZE];
    int vexnum=0, arcnum=0;
};

//定义边的数据类型
template <typename T>
struct ArcNode
{
    // T data;//以后需要什么边内容可以写成一个struct，然后用ArcNode（struct）来定义边
    int index1, index2;
    int weight;
};
//创建邻接矩阵，需要注意，输入的起点和终点不一定是按照顶点的index来的，所以需要在输入的时候将顶点的index和顶点的编号对应起来
//由于只是简单的作业，所以没有写一个函数来将顶点的index和顶点的编号对应起来，而是直接在输入的时候将顶点的index和顶点的编号对应起来，如果是大一点的项目需要进行优化
//这是一个无向图，如果是有向图，需要将arcs[i][j]和arcs[j][i]分开输入
template <typename T>
void CreateAMGraph(AMGraph<T> &graph)
{
    cout << "请输入顶点数和边数：" << endl;
    cin >> graph.vexnum >> graph.arcnum;
    // cout << "请输入顶点信息：" << endl;
    for (int i = 0; i < graph.vexnum; i++)
    {
        // cin >> graph.vexs[i].data;
        graph.vexs[i].index = i;
    }
    for (int i = 0; i < graph.vexnum; i++)
        for (int j = 0; j < graph.vexnum; j++)
            graph.arcs[i][j] = MAXINT;
    for (int i = 0; i < graph.arcnum; i++)
    {
        cout << "请输入边的起点、终点和权重：" << endl;
        int index1, index2, weight;
        cin >> index1 >> index2 >> weight;
        graph.arcs[index1][index2] = weight;
        graph.arcs[index2][index1] = weight;
    }
    return;
};
//给出顶点的位置，返回顶点的index
void GetVexIndexByLocation();
//输出邻接矩阵
template <typename T>
void PrintAMGraph(AMGraph<T> graph)
{
    for (int i = 0; i < graph.vexnum; i++)
    {
        for (int j = 0; j < graph.vexnum; j++)
        {
            cout << graph.arcs[i][j] << " ";
        }
        cout << endl;
    }
    return;
};
//输出无向图的邻接矩阵的深度优先遍历
//调用本函数请先将visited数组初始化为0
template <typename T>
void DFSAMGraph(AMGraph<T> graph, int i, int visited[])
{
    cout << graph.vexs[i].index << " ";
    visited[i] = 1;
    for (int j = 0; j < graph.vexnum; j++)
    {
        if (graph.arcs[i][j] != MAXINT && visited[j] == 0)
        {
            DFSAMGraph(graph, j, visited);
        }
    }
    return;
};
//输出无向图的邻接矩阵的广度优先遍历
//调用本函数请先将visited数组初始化为0
template <typename T>
void BFSAMGraph(AMGraph<T> graph, int i, int visited[])
{
    int queue[MAXSIZE];
    int front = 0, rear = 0;
    cout << graph.vexs[i].index << " ";
    visited[i] = 1;
    queue[rear++] = i;
    while (front != rear)
    {
        int j = queue[front++];
        for (int k = 0; k < graph.vexnum; k++)
        {
            if (graph.arcs[j][k] != MAXINT && visited[k] == 0)
            {
                cout << graph.vexs[k].index << " ";
                visited[k] = 1;
                queue[rear++] = k;
            }
        }
    }
    return;
};
//邻接表的最小生成树，Prim算法
//这里的Prim算法是从顶点0开始的，如果需要从其他顶点开始，需要修改一下代码
template <typename T>
void PrimAMGraph(AMGraph<T> graph)
{
    int lowcost[MAXSIZE];//lowcost[i]表示顶点i到已经加入生成树的顶点的最小权值
    int adjvex[MAXSIZE];//adjvex[i]表示顶点i的最近邻接点
    int visited[MAXSIZE];//visited[i]=1表示顶点i已经加入生成树
    int sum = 0;
    for (int i = 0; i < graph.vexnum; i++)
    {
        lowcost[i] = graph.arcs[0][i];
        adjvex[i] = 0;
        visited[i] = 0;
    }
    visited[0] = 1;
    for (int i = 1; i < graph.vexnum; i++)
    {
        int min = MAXINT;
        int minIndex = 0;
        for (int j = 0; j < graph.vexnum; j++)
        {
            if (visited[j] == 0 && lowcost[j] < min)
            {
                min = lowcost[j];
                minIndex = j;
            }
        }
        sum += min;
        if(minIndex==0)
        {
            cout<<"该图不是连通图，无法生成最小生成树"<<endl;
            return;
        }
        cout << graph.vexs[adjvex[minIndex]].index << " " << graph.vexs[minIndex].index << endl;
        visited[minIndex] = 1;
        for (int j = 0; j < graph.vexnum; j++)
        {
            if (visited[j] == 0 && graph.arcs[minIndex][j] < lowcost[j])
            {
                lowcost[j] = graph.arcs[minIndex][j];
                adjvex[j] = minIndex;
            }
        }
    }
    cout << "最小生成树的权值为：" << sum << endl;
    return;
};
//邻接表的最小生成树，Kruskal算法
template <typename T>
void KruskalAMGraph(AMGraph<T> graph)
{
    ArcNode<T> arc[MAXSIZE];
    int parent[MAXSIZE];
    int sum = 0;
    int count = 0;
    for (int i = 0; i < graph.vexnum; i++)
    {
        parent[i] = i;
    }
    for (int i = 0; i < graph.vexnum; i++)
    {
        for (int j = i + 1; j < graph.vexnum; j++)
        {
            if (graph.arcs[i][j] != MAXINT)
            {
                arc[count].index1 = i;
                arc[count].index2 = j;
                arc[count].weight = graph.arcs[i][j];
                count++;
            }
        }
    }
    //对边按照权值进行排序
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (arc[j].weight > arc[j + 1].weight)
            {
                ArcNode<T> temp = arc[j];
                arc[j] = arc[j + 1];
                arc[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < count; i++)
    {
        int index1 = arc[i].index1;
        int index2 = arc[i].index2;
        int weight = arc[i].weight;
        int parent1 = parent[index1];
        int parent2 = parent[index2];
        while (parent1 != parent[parent1])
            parent1 = parent[parent1];
        while (parent2 != parent[parent2])
            parent2 = parent[parent2];
        if (parent1 != parent2)
        {
            cout << graph.vexs[index1].index << " " << graph.vexs[index2].index << endl;
            sum += weight;
            for (int j = 0; j < graph.vexnum; j++)
            {
                if (parent[j] == parent2)
                    parent[j] = parent1;
            }
        }
    }
    cout << "最小生成树的权值为：" << sum << endl;
    return;
};
#endif
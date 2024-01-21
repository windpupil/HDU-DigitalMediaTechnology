#ifndef _STRUCT_H_
#define _STRUCT_H_
#include <iostream>
using namespace std;
// 结点（景点）结构体
struct Node
{
    int id;//景点编号
    string name;//景点名称
    string introduction;//景点介绍
    Node *next = nullptr;//指向下一个结点
    int tempID; // 这是一个临时ID，用于路径查找、最短路径等数据结构间对应的映射关系    可以防止删除节点后的id错位等问题
};
// 结点（景点）结构体的头结点
// 这里之所以要加一个头结点，是因为该头结点可以存储一些整体的数据，比如结点的个数；
// 其次，在删除结点的时候不会发生直接删除头结点导致地址丢失的问题（大坑），如果不加头结点，可以在删除结点的时候加一个判定条件，如果是第一个结点，就将node指向下一个结点
struct NodeHead
{
    int nodeNum = 0;//结点个数
    Node *next = nullptr;//指向第一个结点
};
// 边结构体
struct Edge
{
    int id;//边编号
    int start;//起点
    int end;//终点
    int length;//长度
    string dirtection;//方向
    string introduction;//介绍
    Edge *next = nullptr;//指向下一条边
    int tempID; // 这是一个临时ID，用于路径查找、最短路径等数据结构间对应的映射关系
};
// 边结构体的头结点
struct EdgeHead
{
    int edgeNum;//边的个数
    Edge *next = nullptr;//指向第一条边
};
NodeHead node;//整个程序的结点存储
EdgeHead edge;//整个程序的边存储

// 邻接表节点结构体
struct AdjTableNode
{
    int end;//终点
    Edge *edge;//边
    AdjTableNode *next = nullptr;//指向下一个邻接表节点
};
// 邻接表头结点
struct AdjTableHead
{
    int start;//起点
    Node *node;//结点
    AdjTableNode *next = nullptr;//指向第一个邻接表节点
};
// 这个邻接表可能换成十字邻接表会好一点，但是我懒，所以我选择每次传入一个原来的邻接表对其销毁，然后新建一个新的邻接表
//  构建邻接表
AdjTableHead *BuildAdjTable(AdjTableHead *adjTableHead = nullptr)
{
    if (adjTableHead != nullptr)
    {
        delete[] adjTableHead;
    }
    Node *nodePointer = node.next;
    AdjTableHead *newAdjTableHead = new AdjTableHead[node.nodeNum + 1];
    // 0号位不用，方便理解
    for (int i = 1; i <= node.nodeNum; i++)
    {
        newAdjTableHead[i].start = nodePointer->id; // 不能写成adjTableHead[i].start = i，因为结点的ID号不一定是按顺序排列的
        newAdjTableHead[i].node = nodePointer;
        nodePointer = nodePointer->next;
        Edge *edgePointer = edge.next;
        AdjTableNode **temp = &(newAdjTableHead[i].next);
        while (edgePointer != nullptr)
        {
            if (edgePointer->start == newAdjTableHead[i].start)
            {
                AdjTableNode *adjTableNode = new AdjTableNode;
                adjTableNode->end = edgePointer->end;
                adjTableNode->edge = edgePointer;
                adjTableNode->next = nullptr;
                *temp = adjTableNode;
                temp = &((*temp)->next);
            }
            edgePointer = edgePointer->next;
        }
    }
    return newAdjTableHead;
}
// 输出结点信息
void PrintNode(Node *node)
{
    while (node != nullptr)
    {
        cout << node->id << " " << node->name << " " << node->introduction << endl;
        node = node->next;
    }
}
// 输出边信息
void PrintEdge(Edge *edge)
{
    while (edge != nullptr)
    {
        cout << edge->id << " " << edge->start << " " << edge->end << " " << edge->length << " " << edge->dirtection << " " << edge->introduction << endl;
        edge = edge->next;
    }
}
// 输出邻接表
void PrintAdjTable(AdjTableHead *adjTableHead)
{
    for (int i = 1; i <= node.nodeNum; i++)
    {
        cout << adjTableHead[i].start << " ";
        AdjTableNode *adjTableNode = adjTableHead[i].next;
        while (adjTableNode != nullptr)
        {
            cout << adjTableNode->end << " ";
            adjTableNode = adjTableNode->next;
        }
        cout << endl;
    }
}
// 给出node的ID，返回tempID
int GetNodeTempIDByID(int ID)
{
    Node *temp = node.next;
    while (temp != nullptr)
    {
        if (temp->id == ID)
        {
            return temp->tempID;
        }
        temp = temp->next;
    }
    return -1;
}
// 给出node的tempID，返回ID
int GetNodeIDByTempID(int tempID)
{
    Node *temp = node.next;
    while (temp != nullptr)
    {
        if (temp->tempID == tempID)
        {
            return temp->id;
        }
        temp = temp->next;
    }
    return -1;
}
// 获取结点的名字
string GetNodeNameByID(int id)
{
    Node *temp = node.next;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            return temp->name;
        }
        temp = temp->next;
    }
    return "未找到";
}
//通过tempID获取结点的名字
string GetNodeNameByTempID(int tempID)
{
    Node *temp = node.next;
    while (temp != nullptr)
    {
        if (temp->tempID == tempID)
        {
            return temp->name;
        }
        temp = temp->next;
    }
    return "未找到";
}
// 获取边的方向
string GetEdgeDirtectionByID(int start, int end)
{
    Edge *temp = edge.next;
    while (temp != nullptr)
    {
        if (temp->start == start && temp->end == end)
        {
            return temp->dirtection;
        }
        temp = temp->next;
    }
    return "未找到";
}
// 通过tempID获取边的方向
string GetEdgeDirtectionByTempID(int start, int end)
{
    Edge *temp = edge.next;
    while (temp != nullptr)
    {
        if (GetNodeTempIDByID(temp->start) == start && GetNodeTempIDByID(temp->end) == end)
        {
            return temp->dirtection;
        }
        temp = temp->next;
    }
    return "未找到";
}
// 获取边的长度
int GetEdgeLengthByID(int start, int end)
{
    Edge *temp = edge.next;
    while (temp != nullptr)
    {
        if (temp->start == start && temp->end == end)
        {
            return temp->length;
        }
        temp = temp->next;
    }
    return -1;
}
// 通过tempID获取边的长度
int GetEdgeLengthByTempID(int start, int end)
{
    Edge *temp = edge.next;
    while (temp != nullptr)
    {
        if (GetNodeTempIDByID(temp->start) == start && GetNodeTempIDByID(temp->end) == end)
        {
            return temp->length;
        }
        temp = temp->next;
    }
    return -1;
}
// 通过ID号输出结点信息
void SearchNodeByID(int id)
{
    Node *temp = node.next;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            cout << temp->id << " " << temp->name << " " << temp->introduction << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "未找到" << endl;
}
// 增加node结点
void AddNode(Node *nodeAdded)
{
    Node *temp = node.next;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = nodeAdded;
    node.nodeNum++;
    cout << "增加成功" << endl;
}
// 删除node结点
void DeleteNode(int id)
{
    Node *temp = node.next;
    Node *pre = node.next;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            if(pre==temp)
                node.next=temp->next;
            else
                pre->next = temp->next;
            delete temp;
            node.nodeNum--;
            cout << "删除成功" << endl;
            PrintNode(node.next);
            return;
        }
        pre = temp;
        temp = temp->next;
    }
    cout << "未找到" << endl;
}
// 增加edge边
void AddEdge(Edge *edgeAdded)
{
    Edge *temp = edge.next;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = edgeAdded;
    cout << "增加成功" << endl;
}
// 删除edge边
void DeleteEdge(int start, int end)
{
    Edge *temp = edge.next;
    Edge *pre = edge.next;
    while (temp != nullptr)
    {
        if (temp->start == start && temp->end == end)
        {
            if(pre==temp)
                edge.next=temp->next;
            else
                pre->next = temp->next;
            delete temp;
            cout << "删除成功" << endl;
            return;
        }
        pre = temp;
        temp = temp->next;
    }
    cout << "未找到" << endl;
}
// 判断是否有重复的ID，有则返回true
bool CheckID(int id)
{
    Node *temp = node.next;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            cout << "ID重复" << endl;
            return true;
        }
        temp = temp->next;
    }
    return false;
}
// 判断Node的ID是否合法，不合法返回false
bool CheckID(int id, int nodeNum)
{
    if (id < 0 )
    {
        cout << "ID不合法" << endl;
        return false;
    }
    return true;
}
// 判断Edge的ID是否重复，重复返回true
bool CheckEdgeID(int id)
{
    Edge *temp = edge.next;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            cout << "ID重复" << endl;
            return true;
        }
        temp = temp->next;
    }
    return false;
}
// 初始化tempID
void InitializeTempID()
{
    Edge *tempEdge = edge.next;
    Node *tempNode = node.next;
    int i = 1;
    while (tempEdge != nullptr)
    {
        tempEdge->tempID = i;
        i++;
        tempEdge = tempEdge->next;
    }
    i = 1;
    while (tempNode != nullptr)
    {
        tempNode->tempID = i;
        i++;
        tempNode = tempNode->next;
    }
}

#endif
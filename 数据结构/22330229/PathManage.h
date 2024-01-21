#ifndef _PATHMANAGE_H_
#define _PATHMANAGE_H_
#include "ManageInformation.h"
#include <vector>
#define MAXINT 32767
// 求两点间最短路径，迪杰斯特拉算法，使用邻接表，输出以start为起点，到各个点的最短路径
void ShortestPathByDijkstra(AdjTableHead *adjTableHead, int start, int end)
{
    bool isSure[node.nodeNum + 1];  // 是否已经确定最短路径
    int distance[node.nodeNum + 1]; // 起点到各点的距离
    int path[node.nodeNum + 1];     // 各点的前驱节点
    // 初始化
    for (int i = 1; i <= node.nodeNum; i++)
    {
        isSure[i] = false;
        distance[i] = MAXINT;
        path[i] = -1;
    }

    // 遍历邻接表，寻找以start为起点的数据结构，存储到temp
    int startTempID = GetNodeTempIDByID(start);
    AdjTableNode *temp = adjTableHead[startTempID].next;
    while (temp != nullptr)
    {
        distance[GetNodeTempIDByID(temp->edge->end)] = temp->edge->length;
        path[GetNodeTempIDByID(temp->edge->end)] = startTempID;
        temp = temp->next;
    }
    isSure[startTempID] = true;
    distance[startTempID] = 0;
    // 主循环
    for (int i = 1; i <= node.nodeNum; i++)
    {
        int min = MAXINT;
        int minIndex = -1;
        // 找到未确定最短路径的最小距离点
        for (int j = 1; j <= node.nodeNum; j++)
        {
            if (!isSure[j] && distance[j] < min)
            {
                min = distance[j];
                minIndex = j;
            }
        }
        if (minIndex == -1)
        {
            break;
        }
        isSure[minIndex] = true;
        // 更新通过这个点可到的点的距离，此时还不一定是最短距离
        temp = adjTableHead[minIndex].next;
        while (temp != nullptr)
        {
            if (!isSure[GetNodeTempIDByID(temp->edge->end)] && distance[GetNodeTempIDByID(temp->edge->end)] > distance[minIndex] + temp->edge->length)
            {
                distance[GetNodeTempIDByID(temp->edge->end)] = distance[minIndex] + temp->edge->length;
                path[GetNodeTempIDByID(temp->edge->end)] = minIndex;
            }
            temp = temp->next;
        }
    }

    int endTempID = GetNodeTempIDByID(end);
    // 输出
    int tempEnd = endTempID;
    if (path[tempEnd] == startTempID)
    {
        cout << GetNodeNameByID(start) << "向" << GetEdgeDirtectionByID(start, end) << "方向"
             << "->" << GetNodeNameByID(end);
        cout << endl
             << "距离为" << distance[endTempID] << endl;
        return;
    }
    else
    {
        vector<int> reversePath; // 反向存储路径      这里其实可以用一个链表
        while (path[tempEnd] != startTempID)
        {
            reversePath.push_back(tempEnd);
            tempEnd = path[tempEnd];
        }
        reversePath.push_back(tempEnd);
        reversePath.push_back(startTempID);
        for (int i = reversePath.size() - 1; i >= 0; i--)
        {
            cout << GetNodeNameByTempID(reversePath[i]);
            if (i != 0)
            {
                cout << "向" << GetEdgeDirtectionByTempID(reversePath[i], reversePath[i - 1]) << "方向" << GetEdgeLengthByTempID(reversePath[i], reversePath[i - 1]) << "->";
            }
        }
    }
    cout << endl
         << "距离为" << distance[endTempID] << endl;
}

void dfs(AdjTableHead *AdjTableHead, int start, int end, bool isVisited[], vector<int> path)
{
    isVisited[start] = true;
    if (start == end)
    {
        for (int i = 0; i < path.size(); i++)
        {
            cout << GetNodeNameByTempID(path[i]);
            if (i != path.size() - 1)
            {
                cout << "->";
            }
        }
        cout << endl;
    }
    else
    {
        AdjTableNode *temp = AdjTableHead[start].next;
        while (temp != nullptr)
        {
            if (!isVisited[GetNodeTempIDByID(temp->edge->end)] && GetNodeTempIDByID(temp->edge->end) != -1)
            {
                path.push_back(GetNodeTempIDByID(temp->edge->end));
                dfs(AdjTableHead, GetNodeTempIDByID(temp->edge->end), end, isVisited, path);
                path.pop_back();
            }
            temp = temp->next;
        }
    }
    isVisited[start] = false;
}
// 求两点间全部路径,不允许有重复的点
void AllPathByID(AdjTableHead *AdjTableHead, int start, int end)
{
    start = GetNodeTempIDByID(start);
    end = GetNodeTempIDByID(end);
    bool isVisited[node.nodeNum + 1] = {0};
    vector<int> path;
    path.push_back(start);
    dfs(AdjTableHead, start, end, isVisited, path);
}

// 求经过的路径长度
int GetPathLength(vector<int> path)
{
    int length = 0;
    for (int i = 0; i < path.size() - 1; i++)
    {
        length += GetEdgeLengthByTempID(path[i], path[i + 1]);
    }
    return length;
}
// 输出经过mustPath的最短路径
void PrintShortestPathThoughMustPoint(vector<vector<int>> &allPath, vector<int> mustPath)
{
    int min = MAXINT;
    int minIndex = -1;
    for (int i = 0; i < allPath.size(); i++)
    {
        int temp = 0;
        for (int j = 0; j < allPath[i].size(); j++)
        {
            for (int k = 0; k < mustPath.size(); k++)
            {
                if (allPath[i][j] == mustPath[k])
                {
                    temp++;
                }
            }
        }
        if (temp == mustPath.size() && GetPathLength(allPath[i]) < min)
        {
            min = GetPathLength(allPath[i]) ;
            minIndex = i;
        }
    }
    if (minIndex == -1)
    {
        cout << "不存在经过必须经过的点的路径" << endl;
    }
    else
    {
        cout << "经过必须经过的点的最短路径为：" << endl;
        for (int i = 0; i < allPath[minIndex].size(); i++)
        {
            cout << GetNodeNameByTempID(allPath[minIndex][i]);
            if (i != allPath[minIndex].size() - 1)
            {
                cout << "->";
            }
        }
        cout << endl;
        cout << "最小路径长度为： " << min << endl;
    }
}
//该重载是用于将所有路径存在allPath中
void dfs(AdjTableHead *AdjTableHead, int start, int end, bool isVisited[], vector<int> path, vector<vector<int>> &allPath)
{
    isVisited[start] = true;
    if (start == end)
    {
        vector<int> temp;
        for (int i = 0; i < path.size(); i++)
        {
            temp.push_back(path[i]);
        }
        allPath.push_back(temp);
    }
    else
    {
        AdjTableNode *temp = AdjTableHead[start].next;
        while (temp != nullptr)
        {
            if (!isVisited[GetNodeTempIDByID(temp->edge->end)] && GetNodeTempIDByID(temp->edge->end) != -1)
            {
                path.push_back(GetNodeTempIDByID(temp->edge->end));
                dfs(AdjTableHead, GetNodeTempIDByID(temp->edge->end), end, isVisited, path, allPath);
                path.pop_back();
            }
            temp = temp->next;
        }
    }
    isVisited[start] = false;
}
// 求两点间全部路径，将所有路径存储到一个二维动态数组中，遍历该二维动态数组，比较是否存在必须经过的地点，如果有，记录路径长度。
void GetShortestPathThoughMustPoint(AdjTableHead *AdjTableHead, int start, int end, vector<int> mustPath)
{
    start = GetNodeTempIDByID(start);
    end = GetNodeTempIDByID(end);
    bool isVisited[node.nodeNum + 1] = {0};
    vector<int> path;
    path.push_back(start);
    vector<vector<int>> allPath;
    dfs(AdjTableHead, start, end, isVisited, path, allPath);
    PrintShortestPathThoughMustPoint(allPath, mustPath);
}
#endif
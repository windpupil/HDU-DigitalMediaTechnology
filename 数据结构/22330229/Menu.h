#ifndef _MENU_H_
#define _MENU_H_
#include "./Struct.h"
#include "./PathManage.h"
// 输出景点信息
void PrintView()
{
    Node *temp = node.next;
    while (temp != nullptr)
    {
        cout << temp->id << " " << temp->name << endl;
        temp = temp->next;
    }
}
void Menu(AdjTableHead *adjTableHead)
{
    cout << "1.查询景点信息" << endl;
    cout << "2.查询两景点间最短路径及路线" << endl;
    cout << "3.查询两景点间所有路径及路线" << endl;
    cout << "4.增加或修改景点信息" << endl;
    cout << "5.删除景点" << endl;
    cout << "6.增加边" << endl;
    cout << "7.删除边" << endl;
    cout << "8.退出" << endl;
    cout << "请输入您的选择：";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1: // 查询景点信息
    {
        PrintView();
        cout << "请输入景点编号：";
        int ID;
        cin >> ID;
        SearchNodeByID(ID);
        break;
    }
    case 2: // 查询两景点间最短路径及路线
    {
        cout << "1.查询两景点间最短路径及路线（无必须经过的景点）" << endl;
        cout << "2.查询两景点间最短路径及路线（有必须经过的景点）" << endl;
        cout << "请输入您的选择：";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            PrintView();
            cout << "请输入起点编号：";
            int start;
            cin >> start;
            cout << "请输入终点编号：";
            int end;
            cin >> end;
            ShortestPathByDijkstra(adjTableHead, start, end);
            break;
        }
        case 2:
        {
            PrintView();
            cout << "请输入起点编号：";
            int start;
            cin >> start;
            cout << "请输入终点编号：";
            int end;
            cin >> end;
            cout << "请输入必须经过的景点编号(请以0作为结束输入)：";
            vector<int> mustPass;
            int temp;
            cin >> temp;
            while (temp != 0)
            {
                temp = GetNodeTempIDByID(temp);
                if(temp == -1)
                {
                    cout << "输入错误，请重新输入" << endl;
                    Menu(adjTableHead);
                    return;
                }
                mustPass.push_back(temp);
                cin >> temp;
            }
            GetShortestPathThoughMustPoint(adjTableHead, start, end, mustPass);
            break;
        }
        default:
        {
            cout << "输入错误，请重新输入" << endl;
            Menu(adjTableHead);
            break;
        }
        }
        break;
    }
    case 3: // 查询两景点间所有路径及路线
    {
        PrintView();
        cout << "请输入起点编号：";
        int start;
        cin >> start;
        cout << "请输入终点编号：";
        int end;
        cin >> end;
        AllPathByID(adjTableHead, start, end);
        break;
    }
    case 4: // 增加或修改景点信息
    {
        cout << "请输入景点ID: ";
        int ID;
        cin >> ID;
        // 检查ID是否合法
        if (CheckID(ID, node.nodeNum) == false)
            break;

        cout << "请输入景点名称：";
        string name;
        cin >> name;
        cout << "请输入景点介绍：";
        string introduction;
        cin >> introduction;

        if (CheckID(ID))
        {
            // 修改结点
            Node *temp = node.next;
            while (temp != nullptr)
            {
                if (temp->id == ID)
                {
                    temp->name = name;
                    temp->introduction = introduction;
                    break;
                }
                temp = temp->next;
            }
            cout << "修改成功" << endl;
        }
        else
        {
            // 增加结点
            Node *newNode = new Node;
            newNode->id = ID;
            newNode->name = name;
            newNode->introduction = introduction;
            AddNode(newNode);
        }
        InitializeTempID();
        break;
    }
    case 5: // 删除景点
    {
        PrintView();
        cout << "请输入要删除的景点编号：";
        int id;
        cin >> id;
        if (CheckID(id, node.nodeNum) == false)
            break;
        DeleteNode(id);
        InitializeTempID();
        break;
    }
    case 6: // 增加边
    {
        cout << "请输入ID号：";
        int id;
        cin >> id;
        if (CheckEdgeID(id) == true)
            break;
        PrintView();
        cout << "请输入起点编号：";
        int start;
        cin >> start;
        if (CheckID(start, node.nodeNum) == false)
            break;
        cout << "请输入终点编号：";
        int end;
        cin >> end;
        if (CheckID(end, node.nodeNum) == false)
            break;
        cout << "请输入边的长度：";
        int length;
        cin >> length;
        if (length <= 0)
        {
            cout << "长度必须大于0" << endl;
            break;
        }
        cout << "请输入边的方向：";
        string dirtection;
        cin >> dirtection;
        cout << "请输入边的介绍：";
        string introduction;
        cin >> introduction;
        Edge *newEdge = new Edge;
        newEdge->id = id;
        newEdge->start = start;
        newEdge->end = end;
        newEdge->length = length;
        newEdge->dirtection = dirtection;
        newEdge->introduction = introduction;
        AddEdge(newEdge);
        InitializeTempID();
        break;
    }
    case 7: // 删除边
    {
        PrintView();
        cout << "请输入起点编号：";
        int start;
        cin >> start;
        if (CheckID(start, node.nodeNum) == false)
            break;
        cout << "请输入终点编号：";
        int end;
        cin >> end;
        if (CheckID(end, node.nodeNum) == false)
            break;
        DeleteEdge(start, end);
        InitializeTempID();
        break;
    }
    case 8: // 退出
    {
        exit(0);
        break;
    }
    default: // 输入错误
    {
        cout << "输入错误，请重新输入" << endl;
        Menu(adjTableHead);
        break;
    }
    }
}
#endif
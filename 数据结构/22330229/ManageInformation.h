#ifndef _MANAGEINFORMATION_H_
#define _MANAGEINFORMATION_H_
#include <fstream>
#include <ostream>
#include "./Struct.h"
#define MAXLENGTH 50
// 读取文件并存储
void ReadFile()
{
    Node **nodePointer = &node.next;
    Edge **edgePointer = &edge.next;

    ifstream file;
    // file.open("Information.json", ios::in);//一般情况下是可以的，但是我的相对路径有问题，原因是我在vscode配置c环境时，修改了默认路径
    file.open("E:/datastructure/Project/Information.json", ios::in);
    if (!file.is_open())
    {
        cout << "文件打开失败";
        exit(1);
    }
    string str;
    while (getline(file, str))
    {
        if (str == "    \"points\": [") // 这里的优化方式有正则表达式、修改json数据格式，比如id前加一个#，检索数据时就以#为标志
        {
            while (getline(file, str))
            {
                if (str == "    ],")
                {
                    break;
                }
                else if (str == "        {")
                {
                    Node *tempNode = new Node;

                    getline(file, str);
                    tempNode->id = stoi(str.substr(str.find(":") + 1, MAXLENGTH));//因为stoi，读到""也没事
                    getline(file, str);
                    tempNode->name = str.substr(str.find(":") + 3, str.find(",") - str.find(":") - 4);//这里在数据里添加读取的标识符比较好，比如#
                    getline(file, str);
                    tempNode->introduction = str.substr(str.find(":") + 3, str.find("#") - str.find(":") - 3);
                    getline(file, str);

                    *nodePointer = tempNode;
                    nodePointer = &(tempNode->next);
                    node.nodeNum++;
                }
            }
        }
        else if (str == "    \"edges\": [")
        {
            while (getline(file, str))
            {
                if (str == "    ],")
                {
                    break;
                }
                else if (str == "        {")
                {
                    Edge *tempEdge = new Edge;

                    getline(file, str);
                    tempEdge->id = stoi(str.substr(str.find(":") + 2,MAXLENGTH));
                    getline(file, str);
                    tempEdge->start = stoi(str.substr(str.find(":") + 2, MAXLENGTH));
                    getline(file, str);
                    tempEdge->end = stoi(str.substr(str.find(":") + 2, MAXLENGTH));
                    getline(file, str);
                    tempEdge->length = stoi(str.substr(str.find(":") + 2, MAXLENGTH));
                    getline(file, str);
                    tempEdge->dirtection = str.substr(str.find(":") + 3, 6);//这里是按字节数来算的，utf-8中一个汉字占3个字节，所以这里是6
                    getline(file, str);
                    tempEdge->introduction = str.substr(str.find(":") + 2, str.find("#") - str.find(":") - 3);
                    getline(file, str);

                    *edgePointer = tempEdge;
                    edgePointer = &tempEdge->next;
                    edge.edgeNum++;
                }
            }
        }
    }
    file.close();
}

// 打开文件并输入，如果文件不存在则创建
// 不能用中文作为name！否则会报错！
void WriteFile(string name ,string content)
{
    ofstream file;
    file.open("E:/datastructure/Project/output/" +name, ios::out);
    if (!file.is_open())
    {
        cout << "文件打开失败";
        exit(1);
    }
    // file << content;这样读取无法读取到换行符
}

//打开文件，并追加内容
void AppFile(string name, string content)
{
    ofstream file;
    file.open("E:/datastructure/Project/output/" + name, ios::app);
    if (!file.is_open())
    {
        cout << "文件打开失败";
        exit(1);
    }
    file << content;
}

#endif
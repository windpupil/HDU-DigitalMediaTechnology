#ifndef _BITNODE_H_
#define _BITNODE_H_
#include <iostream>
using namespace std;
#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int Status;
template <typename T>
// 定义二叉树节点
struct BiTNode
{
    T data;
    struct BiTNode<T> *left=NULL;
    struct BiTNode<T> *right=NULL;
};
typedef BiTNode<int> BiTNodeInt, *BiTNodeIntPointer;
typedef BiTNode<char> BiTNodeChar, *BiTNodeCharPointer;
// 创建树
template <typename T>
Status CreateBiTNode(BiTNode<T>* &parent)
{
    parent = new BiTNode<T>;
    char input;
    cin >> input;
    if (input == '#')
    {
        parent = NULL;
    }
    else
    {
        //如果T是int类型，需要将input转换为int类型
        if (typeid(T) == typeid(int))
        {
            parent->data = input - '0';
        }
        else
        {
            parent->data = input;
        }
        CreateBiTNode(parent->left);
        CreateBiTNode(parent->right);
    }
    return OK;
}
//中序输出树的节点
template <typename T>
void PrintBiTNodeWithMiddle(BiTNode<T> tree)
{
    if (tree.left != NULL)
    {
        PrintBiTNodeWithMiddle(*tree.left);
    }
    cout << tree.data << " ";
    if (tree.right != NULL)
    {
        PrintBiTNodeWithMiddle(*tree.right);
    }
    return;
}
//前序输出树的节点
template <typename T>
void PrintBiTNodeWithPre(BiTNode<T> tree)
{
    cout << tree.data << " ";
    if (tree.left != NULL)
    {
        PrintBiTNodeWithPre(*tree.left);
    }
    if (tree.right != NULL)
    {
        PrintBiTNodeWithPre(*tree.right);
    }
    return;
}
//树的查找操作
//树的插入操作
//求树的深度
template <typename T>
int GetTreeDepth(BiTNode<T> *parent)
{
    if (parent == NULL)
    {
        return 0;
    }
    else
    {
        int leftDepth = GetTreeDepth(parent->left);
        int rightDepth = GetTreeDepth(parent->right);
        return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
    }
}
#endif
// 本题为6.52的代码，求繁茂度
#include "../DataStructure/BiTNode.h"
template <typename T>
struct Queue
{
    int front = 0, rear = 0;
    BiTNode<T> *data[MAXSIZE];
    int level[MAXSIZE] = {0}; // 存储各结点所在的层数
    int size = 0;             // 队列中元素的个数
};
template <typename T>
Status EnQueue(Queue<T> &qu, BiTNode<T> *node, int level)
{
    if (qu.size == MAXSIZE)
    {
        return ERROR;
    }
    else
    {
        qu.data[qu.rear] = node;
        qu.level[qu.rear++] = level;
        qu.size++;
    }
    return OK;
}
template <typename T>
int GetTreeDensity(BiTNode<T> *parent)
{
    Queue<T> qu;
    int maxLevel = 1;
    if (parent == NULL)
    {
        return 0;
    }
    else
    {
        EnQueue(qu, parent, 1);
        // 层序遍历
        while (qu.size != 0)
        {
            if (qu.data[qu.front]->left != NULL)
            {
                EnQueue(qu, qu.data[qu.front]->left, qu.level[qu.front] + 1);
            }
            if (qu.data[qu.front]->right != NULL)
            {
                EnQueue(qu, qu.data[qu.front]->right, qu.level[qu.front] + 1);
            }
            maxLevel = qu.level[qu.front];
            qu.front++;
            qu.size--;
        }
    }
    int count[maxLevel+1] = {0};
    for (int i = 0; i < qu.rear; i++)
    {
        count[qu.level[i]]++;
    }
    int max = 0;
    for (int i = 1; i < maxLevel+1; i++)
    {
        if (count[i]*i > max)
        {
            max = count[i]*i;
        }
    }
    return max;
}
int main()
{
    BiTNodeIntPointer tree;
    CreateBiTNode(tree);
    cout << GetTreeDensity(tree) << endl;
}
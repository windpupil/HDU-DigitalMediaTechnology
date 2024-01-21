#ifndef _SQQUEUE_H_
#define _SQQUEUE_H_

#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int Status;
// 定义队列
template <typename T>
struct SqQueue
{
    T data[MAXSIZE];
    int front, rear;
    int size;
};
typedef SqQueue<int> SqQueueInt, *SqQueueIntPointer;
typedef SqQueue<char> SqQueueChar, *SqQueueCharPointer;
// 初始化队列, 也是重置队列
template <typename T>
Status InitSqQueue(SqQueue<T> &S)
{
    S.front = 0;
    S.rear = 0;
    S.size = 0;
    return OK;
}
// 将元素入队
template <typename T>
Status PushSqQueue(SqQueue<T> &S, T e)
{
    if (S.size == MAXSIZE)
    {
        return ERROR;
    }
    S.data[S.rear] = e;
    S.rear = (S.rear + 1) % MAXSIZE;
    S.size++;
    return OK;
}
//将元素出队
template <typename T>
Status PopSqQueue(SqQueue<T> &S, T *e)
{
    if (S.size == 0)
    {
        return ERROR;
    }
    *e = S.data[S.front];
    S.front = (S.front + 1) % MAXSIZE;
    S.size--;
    return OK;
}
//获取队头元素
template <typename T>
Status GetHeadSqQueue(SqQueue<T> S, T *e)
{
    if (S.size == 0)
    {
        return ERROR;
    }
    *e = S.data[S.front];
    return OK;
}
//判断队列是否为空
template <typename T>
bool IsEmptySqQueue(SqQueue<T> S)
{
    if (S.size == 0)
        return true;
    else
        return false;
}
//判断队列是否为满
template <typename T>
bool IsFullSqQueue(SqQueue<T> S)
{
    if (S.size == MAXSIZE)
        return true;
    else
        return false;
}
#endif
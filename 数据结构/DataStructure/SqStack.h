#ifndef _SQSTACK_H_
#define _SQSTACK_H_
#include <iostream>
using namespace std;
#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int Status;
template <typename T>
// 定义栈
struct SqStack
{
    T data[MAXSIZE];
    int top;
};
typedef SqStack<int> SqStackInt, *SqStackIntPointer;
typedef SqStack<char> SqStackChar, *SqStackCharPointer;
// 初始化栈
template <typename T>
Status InitSqStack(SqStack<T> *S)
{
    S->top = 0;
    return OK;
}
// 入栈
template <typename T>
Status PushSqStack(SqStack<T> *S, T e)
{
    if (S->top == MAXSIZE)
    {
        return ERROR;
    }
    else
    {
        S->data[S->top] = e;
        S->top++;
        return OK;
    }
}
// 出栈
template <typename T>
Status PopSqStack(SqStack<T> *S, T *e)
{
    if (S->top == 0)
    {
        return ERROR;
    }
    else
    {
        S->top--;
        *e = S->data[S->top];
        return OK;
    }
}
#endif
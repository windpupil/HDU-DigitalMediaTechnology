#ifndef _SEQLIST_H_
#define _SEQLIST_H_

#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int ElemType;
typedef int Status;
typedef struct SeqList
{
    ElemType *elem;
    // ElemType elem[MAXSIZE];
    int length;
} SeqList, *SeqListPointer;

Status InitSeqList(SeqList *L) // 初始化
{
    L->elem = new ElemType[MAXSIZE];
    if (!L->elem)
    {
        return ERROR; // 存储分配失败(申请失败)
    }
    L->length = 0;
    return OK;
}
Status CreateSeqList(SeqList *L) // 为顺序表赋值
{
    int number;
    cout << "请输入顺序表的长度：" << endl;
    cin >> number;
    cout << "请输入顺序表的元素：" << endl;
    for (int i = 0; i < number; i++)
    {
        cin >> L->elem[i];
    }
    L->length = number;
    return OK;
}
// 插入x使顺序表依旧有序
Status InsertSeqList(SeqList *L, ElemType x)
{
    // 检查数据合法性
    if (L->length >= MAXSIZE)
    {
        cout << "顺序表已满，无法插入！" << endl;
        return ERROR;
    }
    L->length++;
    for (int i = (L->length) - 2; i >= 0; i--)
    {
        if (x < L->elem[i])
        {
            L->elem[i + 1] = L->elem[i];
        }
        else
        {
            L->elem[i + 1] = x;
            return OK;
        }
    }
    return OK;
}

// 比较A和B大小的函数,返回值为1则A>B,返回值为-1则A<B,返回值为0则A=B
Status CompareSeqList(SeqList A, SeqList B)
{
    int i = 0;
    while (i < A.length && i < B.length)
    {
        if (A.elem[i] < B.elem[i])
        {
            return -1;
        }
        else if (A.elem[i] > B.elem[i])
        {
            return 1;
        }
        i++;
    }
    if (A.length < B.length)
    {
        return -1;
    }
    else if (A.length > B.length)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//删除某个元素
Status DeleteSeqList(SeqList *L, ElemType x)
{
    int i = 0;
    while (i < L->length)
    {
        if (L->elem[i] == x)
        {
            for (int j = i; j < L->length - 1; j++)
            {
                L->elem[j] = L->elem[j + 1];
            }
            L->length--;
            return OK;
        }
        i++;
    }
    return ERROR;
}
#endif
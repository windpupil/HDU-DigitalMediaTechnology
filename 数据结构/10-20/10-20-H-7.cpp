// 本代码为2.29题的代码
#include ".\DataStructure\SeqList.h"
#include <algorithm>
int main()
{
    SeqList A, B, C;
    InitSeqList(&A);
    InitSeqList(&B);
    InitSeqList(&C);
    CreateSeqList(&A);
    CreateSeqList(&B);
    CreateSeqList(&C);
    SeqList same;
    InitSeqList(&same);
    int i = 0, j = 0;
    while (i < B.length && j < C.length)
    {
        if (B.elem[i] == C.elem[j])
        {
            same.length++;
            same.elem[same.length - 1] = B.elem[i];
            i++;
            j++;
        }
        else if (B.elem[i] < C.elem[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    i = 0;
    j = 0;
    while (i < A.length && j < same.length)
    {
        if (A.elem[i] == same.elem[j])
        {
            DeleteSeqList(&A, A.elem[i]);
        }
        else if (A.elem[i] < same.elem[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    for (int i = 0; i < A.length; i++)
    {
        cout << A.elem[i] << " ";
    }
}
//时间复杂度为O(n)
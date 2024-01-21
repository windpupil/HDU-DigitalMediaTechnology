//本代码为2.11题的代码，实现了在顺序表中插入一个元素
#include ".\DataStructure\SeqList.h"
int main()
{
    SeqList L;
    InitSeqList(&L);
    CreateSeqList(&L);
    cout<<"请输入要插入的元素：";
    int x;
    cin>>x;
    InsertSeqList(&L,x);
    cout<<"插入后的顺序表为：";
    for(int i=0;i<L.length;i++)
    {
        cout<<"第"<<i+1<<"个元素为："<<L.elem[i]<<endl;
    }
    return 0;
}
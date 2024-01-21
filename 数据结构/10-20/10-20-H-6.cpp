// 本代码为2.22题的代码，实现了单链表的原地逆置功能
#include ".\DataStructure\SingleLinkList.h"
int main()
{
    SingleLinkListPointer L;
    InitList(&L);
    CreateSingleLinkListPointerTail(L);
    InverseSingleLinkList(L);
    PrintSingleLinkList(L);
}
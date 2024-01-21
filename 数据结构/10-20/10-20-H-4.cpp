// 本代码为2.14题的代码，实现了单链表的求表长功能
#include ".\DataStructure\SingleLinkList.h"
int main()
{
    SingleLinkListPointer L;
    InitList(&L);
    CreateSingleLinkListPointerTail(L);
    int number = GetSingleLinkListLength(L);
    cout << number << endl;
}
// 本代码为2.13题的代码，实现了单链表的查找结点功能
#include ".\DataStructure\SingleLinkList.h"
int main(){
    SingleLinkListPointer L;
    InitList(&L);
    CreateSingleLinkListPointerTail(L);
    SingleLinkListPointer temp = GetSingleLinkListElem(*L, 3);//返回了第一个值为3的节点
    cout << "该节点值为：" << temp->data << endl;
    return 0;
}
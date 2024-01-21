// 本代码为2.30题的代码
#include ".\DataStructure\SingleLinkList.h"
int main()
{
    SingleLinkListPointer A, B, C;
    InitList(&A);
    InitList(&B);
    InitList(&C);
    CreateSingleLinkListPointerTail(A);
    CreateSingleLinkListPointerTail(B);
    CreateSingleLinkListPointerTail(C);
    SingleLinkListPointer same;
    InitList(&same);
    SingleLinkListPointer temp1 = B->next;
    SingleLinkListPointer temp2 = C->next;
    SingleLinkListPointer thisNode = same;
    while(temp1 && temp2)
    {
        if (temp1->data == temp2->data)
        {
            InsertSingleLinkListNextNode(thisNode, temp1->data);
            thisNode = thisNode->next;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if (temp1->data < temp2->data)
        {
            temp1 = temp1->next;
        }
        else
        {
            temp2 = temp2->next;
        }
    }
    temp1 = A;
    temp2 = same;
    // PrintSingleLinkList(same);
    while(temp1->next && temp2->next)
    {
        if (temp1->next->data == temp2->next->data)
        {
            SingleLinkListPointer temp = temp1->next;
            temp1->next = temp1->next->next;
            delete temp;
        }
        else if (temp1->next->data < temp2->next->data)
        {
            temp1 = temp1->next;
        }
        else
        {
            temp2 = temp2->next;
        }
    }
    PrintSingleLinkList(A);
}
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int ElemType;
typedef int Status;
// 定义链表节点结构体SingleLinkList
typedef struct SingleLinkList
{
    ElemType coefficient;
    ElemType count;
    struct SingleLinkList *next;
} SingleLinkList, *SingleLinkListPointer;

// 初始化链表
Status InitList(SingleLinkListPointer *L)
{
    *L = new SingleLinkList;
    (*L)->next = NULL;
    return OK;
}
// 尾插法创建单链表
Status CreateSingleLinkListPointerTail(SingleLinkListPointer L)
{
    int number;
    cout << "请输入链表的长度：" << endl;
    cin >> number;
    cout << "请输入链表的元素：" << endl;
    SingleLinkListPointer tail = L;
    for (int i = 0; i < number; i++)
    {
        SingleLinkListPointer temp = new SingleLinkList;
        cin >> temp->coefficient;
        cin >> temp->count;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
    }
    return OK;
}
SingleLinkListPointer AddSingleLinkList(SingleLinkListPointer A, SingleLinkListPointer B)
{
    SingleLinkListPointer C = new SingleLinkList;
    SingleLinkListPointer tempA = A->next;
    SingleLinkListPointer tempB = B->next;
    SingleLinkListPointer tempC = C;
    while (tempA && tempB)
    {
        SingleLinkListPointer temp = new SingleLinkList;
        if (tempA->count == tempB->count)
        {
            temp->coefficient = tempA->coefficient + tempB->coefficient;
            temp->count = tempA->count;
            tempA = tempA->next;
            tempB = tempB->next;
        }
        else if (tempA->count > tempB->count)
        {
            temp->coefficient = tempB->coefficient;
            temp->count = tempB->count;
            tempB = tempB->next;
        }
        else
        {
            temp->coefficient = tempA->coefficient;
            temp->count = tempA->count;
            tempA = tempA->next;
        }
        temp->next = NULL;
        tempC->next = temp;
        tempC = tempC->next;
    }
    while (tempA)
    {
        SingleLinkListPointer temp = new SingleLinkList;
        temp->coefficient = tempA->coefficient;
        temp->count = tempA->count;
        temp->next = NULL;
        tempC->next = temp;
        tempA = tempA->next;
    }
    while (tempB)
    {
        SingleLinkListPointer temp = new SingleLinkList;
        temp->coefficient = tempB->coefficient;
        temp->count = tempB->count;
        temp->next = NULL;
        tempC->next = temp;
        tempB = tempB->next;
    }
    return C;
}

// 输出链表的值
Status PrintSingleLinkList(SingleLinkListPointer L)
{
    SingleLinkListPointer temp = L->next;
    while (temp)
    {
        if (temp->coefficient == 0)
        {
            temp = temp->next;
            continue;
        }
        if(temp->count==0)
        {
            cout << temp->coefficient << " +";
        }
        else if(temp->next==NULL)
        {
            cout << temp->coefficient << "X^" << temp->count;
            break;
        }
        else
        {
            cout << temp->coefficient << "X^" << temp->count << " +";
        }
        if (temp->next != NULL)
        {
            temp = temp->next;
        }
        else
        {
            break;
        }
    }
    cout << endl;
    return OK;
}
int main()
{
    SingleLinkListPointer A, B, C;
    InitList(&A);
    InitList(&B);
    InitList(&C);
    CreateSingleLinkListPointerTail(A);
    CreateSingleLinkListPointerTail(B);
    C = AddSingleLinkList(A, B);
    PrintSingleLinkList(C);
}
#ifndef _SINGLELINKLIST_H_
#define _SINGLELINKLIST_H_

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
    ElemType data;
    struct SingleLinkList *next;
} SingleLinkList, *SingleLinkListPointer;

// 初始化链表
Status InitList(SingleLinkListPointer *L)
{
    *L = new SingleLinkList;
    (*L)->next = NULL;
    return OK;
}

// 头插法创建单链表
Status CreateSingleLinkListPointerHead(SingleLinkListPointer L)
{
    int number;
    cout << "请输入链表的长度：" << endl;
    cin >> number;
    cout << "请输入链表的元素：" << endl;
    for (int i = 0; i < number; i++)
    {
        SingleLinkListPointer temp = new SingleLinkList;
        cin >> temp->data;
        temp->next = L->next;
        L->next = temp;
    }
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
        cin >> temp->data;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
    }
    return OK;
}
// 查找链表中第一个与x值相等的节点
SingleLinkListPointer GetSingleLinkListElem(SingleLinkList L, ElemType x)
{
    SingleLinkListPointer temp = (&L)->next;
    int number = 0; // number为第几个节点，而非下标
    while (temp)
    {
        number++;
        if (temp->data == x)
        {
            return temp;
        }
        temp = temp->next;
    }
    return ERROR; // 未找到
}
// 返回链表的长度
int GetSingleLinkListLength(SingleLinkListPointer L)
{
    SingleLinkListPointer temp;
    int number = 0;
    if (L)
    {
        temp = L->next;
        while (temp)
        {
            number++;
            temp = temp->next;
        }
    }
    return number;
}

//在thisNode节点之后创建新节点，data为newData
Status InsertSingleLinkListNextNode(SingleLinkListPointer thisNode, ElemType newData)
{
    SingleLinkListPointer temp = new SingleLinkList;
    temp->data = newData;
    temp->next = thisNode->next;
    thisNode->next = temp;
    return OK;
}

//合并两个链表
SingleLinkListPointer MergeSingleLinkList(SingleLinkListPointer ha, SingleLinkListPointer hb)
{
    SingleLinkListPointer hc;
    InitList(&hc);
    SingleLinkListPointer tempha = ha->next;
    SingleLinkListPointer temphb = hb->next;
    SingleLinkListPointer laterNode;
    laterNode = new SingleLinkList;
    hc->next = laterNode;
    laterNode->next = NULL;
    if(GetSingleLinkListLength(ha) > GetSingleLinkListLength(hb))
    {
        laterNode->data = temphb->data;
        temphb = temphb->next;
        SingleLinkListPointer insertNodeha = hc;
        SingleLinkListPointer insertNodehb=hc->next;
        while(tempha)
        {
            InsertSingleLinkListNextNode(insertNodeha, tempha->data);
            insertNodeha = insertNodeha->next;
            tempha = tempha->next;
            if(temphb)
            {
                InsertSingleLinkListNextNode(insertNodehb, temphb->data);
                insertNodehb = insertNodehb->next;
                temphb = temphb->next;
            }
        }
    }
    else
    {
        laterNode->data = tempha->data;
        tempha = tempha->next;
        SingleLinkListPointer insertNodehb = hc;
        SingleLinkListPointer insertNodeha=hc->next;
        while(temphb)
        {
            InsertSingleLinkListNextNode(insertNodehb, temphb->data);
            insertNodehb = insertNodehb->next;
            temphb = temphb->next;
            if(tempha)
            {
                InsertSingleLinkListNextNode(insertNodeha, tempha->data);
                insertNodeha = insertNodeha->next;
                tempha = tempha->next;
            }
        }
    }
    return hc;
}
//输出链表的值
Status PrintSingleLinkList(SingleLinkListPointer L)
{
    SingleLinkListPointer temp = L->next;
    while (temp)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
    return OK;
}

//就地逆置链表，头插法
//head变量存储的是头节点的地址
//temp变量存储的是下一个要插入的节点的地址
//insertNode变量存储的是当前要插入的节点的地址
// Status InverseSingleLinkList(SingleLinkListPointer head)
// {
//     SingleLinkListPointer insertNode = head->next;
//     head->next = NULL;
//     SingleLinkListPointer temp;
//     while(insertNode)
//     {
//         temp = insertNode->next;
//         insertNode->next = head->next;
//         head->next = insertNode;
//         insertNode = temp;
//     }
//     return OK;
// }

//就地逆置链表，递归法
//算法概括：依次计录节点为temp，并将头节点和该节点（永远是首元节点）断开，头结点指向新的首元节点。递归直至剩最后一个节点，此时开始回溯，将temp节点尾插即可
Status InverseSingleLinkList(SingleLinkListPointer head)
{
    if(head->next == NULL || head->next->next == NULL)//head->next==NULL是链表为空的情况，head->next->next==NULL是链表只有一个节点的情况
    {
        return OK;
    }
    else
    {
        SingleLinkListPointer temp = head->next;
        head->next = temp->next;
        InverseSingleLinkList(head);
        temp->next->next = temp;
        temp->next = NULL;
        return OK;
    }
}
#endif
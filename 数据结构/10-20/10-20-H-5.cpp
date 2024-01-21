// 本代码为2.15题的代码
#include ".\DataStructure\SingleLinkList.h"
int main()
{
    SingleLinkListPointer ha, hb;
    InitList(&ha);
    InitList(&hb);
    CreateSingleLinkListPointerTail(ha);
    CreateSingleLinkListPointerTail(hb);
    SingleLinkListPointer hc;
    hc = MergeSingleLinkList(ha, hb);
    //输出hc的数据
    SingleLinkListPointer temp = hc->next;
    while(temp)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    // 看上去时间复杂度是O（max（m，n）），但我觉得说是O（m+n）好像也没问题。
    // 不是不会直接俩循环，是想优化算法让他看上去像是O（max（m，n））
}
//本代码为2.12题的代码，实现了比较两个顺序表的大小
#include ".\DataStructure\SeqList.h"
int main() {
    // SeqList A = {{3, 2, 1}, 3};
    // SeqList B = {{1}, 1};
    SeqList A;
    SeqList B;
    InitSeqList(&A);
    InitSeqList(&B);
    CreateSeqList(&A);
    CreateSeqList(&B);
    int result = CompareSeqList(A, B);
    if (result == -1) {
        cout<<"A < B"<<endl;
    } else if (result == 1) {
        cout<<"A > B"<<endl;
    } else {
        cout<<"A = B"<<endl;
    }
    return 0;
}

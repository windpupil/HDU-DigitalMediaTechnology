// 本题为6.51的代码,求算术表达式
#include "../DataStructure/BiTNode.h"
int main()
{
    BiTNodeCharPointer tree;
    CreateBiTNode(tree);
    PrintBiTNodeWithMiddle(*tree);
    return 0;
}
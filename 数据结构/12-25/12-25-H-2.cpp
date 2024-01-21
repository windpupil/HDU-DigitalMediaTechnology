//从大到小输出给定二叉排序树中所有关键字不小于x的数据元素
#include "../DataStructure/BiTNode.h"
void PrintNumberFromLargeToSmall(BiTNodeIntPointer tree, int x)
{
    if (tree == NULL)
        return;
    if (tree->data >= x)
    {
        PrintNumberFromLargeToSmall(tree->right, x);
        cout << tree->data << endl;
        PrintNumberFromLargeToSmall(tree->left, x);
    }
    else
        PrintNumberFromLargeToSmall(tree->right, x);
}
int main()
{
    BiTNodeIntPointer tree;
    CreateBiTNode(tree);
    PrintNumberFromLargeToSmall(tree, 4);
    return 0;
}

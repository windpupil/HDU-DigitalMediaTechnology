//实现二叉排序树删除一个值为e的节点
#include "../DataStructure/BiTNode.h"
void DeleteNode(BiTNodeIntPointer &tree, int e)
{
    if (tree == NULL)
        return;
    if (tree->data == e)
    {
        if (tree->left == NULL && tree->right == NULL)
        {
            tree = NULL;//这里其实没有真正删除，只是将指针置空；如果delete的话需要将父节点的指针置空
            return;
        }
        else if (tree->left == NULL)
        {
            tree = tree->right;
            return;
        }
        else if (tree->right == NULL)
        {
            tree = tree->left;
            return;
        }
        else
        {
            BiTNodeIntPointer temp = tree->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            tree->data = temp->data;
            DeleteNode(tree->right, temp->data);
            return;
        }
    }
    else if (tree->data > e)
    {
        DeleteNode(tree->left, e);
        return;
    }
    else
    {
        DeleteNode(tree->right, e);
        return;
    }
}
int main()
{
    BiTNodeIntPointer tree;
    CreateBiTNode(tree);
    cout<<"删除5"<<endl;
    DeleteNode(tree, 5);
    PrintBiTNodeWithMiddle(*tree);
    cout << endl;
    cout<<"头结点是 "<<tree->data<<endl;

    cout<<"删除7"<<endl;
    DeleteNode(tree, 7);
    PrintBiTNodeWithMiddle(*tree);
    cout << endl;

    cout<<"删除2"<<endl;
    DeleteNode(tree, 2);
    PrintBiTNodeWithMiddle(*tree);
    cout << endl;
    return 0;
}
//二叉树后续遍历非递归算法
#include "../DataStructure/BiTNode.h"
#include "../DataStructure/SqStack.h"
//方法1：额外增加一个布尔数组记录节点被访问的次数，第一次被访问时，入栈，第二次访问更改布尔值，第三次弹出；
// template <typename T>
// void PrintBiTNodeWithPost(BiTNode<T> tree)
// {
//     BiTNode<T> *temp = &tree;
//     SqStack<BiTNode<T> *> stack;
//     InitSqStack(&stack);
//     bool isSecond[MAXSIZE]={0};
//     while (temp != NULL || stack.top != 0)
//     {
//         if (temp != NULL)
//         {
//             PushSqStack(&stack, temp);
//             temp = temp->left;
//         }
//         else
//         {
//             temp = stack.data[stack.top - 1];
//             if (isSecond[temp->data])
//             {
//                 PopSqStack(&stack, &temp);
//                 cout << temp->data << " ";
//                 temp = NULL;
//             }
//             else
//             {
//                 isSecond[temp->data] = true;
//                 temp = temp->right;
//             }
//         }
//     }
// }

//方法2：使用双栈，先按根右左的方式将其弹入栈，在将其转移至新栈，即为颠倒后左右根的顺序
// template <typename T>
// void PrintBiTNodeWithPost(BiTNode<T> tree)
// {
//     BiTNode<T> *temp = &tree;
//     SqStack<BiTNode<T> *> stack1, stack2;
//     InitSqStack(&stack1);
//     InitSqStack(&stack2);
//     PushSqStack(&stack1, temp);
//     while (stack1.top != 0)
//     {
//         PopSqStack(&stack1, &temp);
//         PushSqStack(&stack2, temp);
//         if (temp->left != NULL)
//         {
//             PushSqStack(&stack1, temp->left);
//         }
//         if (temp->right != NULL)
//         {
//             PushSqStack(&stack1, temp->right);
//         }
//     }
//     while (stack2.top != 0)
//     {
//         PopSqStack(&stack2, &temp);
//         cout << temp->data << " ";
//     }
//     return;
// }

//方法3：叶子节点必定直接输出，遍历节点并和上次遍历的节点比较，如果上次节点时该次节点的右节点，那么输出该节点
template <typename T>
void PrintBiTNodeWithPost(BiTNode<T> tree)
{
    BiTNode<T> *temp = &tree;
    SqStack<BiTNode<T> *> stack;
    InitSqStack(&stack);
    BiTNode<T> *last = NULL;//上次遍历的节点
    while (temp != NULL || stack.top != 0)
    {
        if (temp != NULL)
        {
            PushSqStack(&stack, temp);
            temp = temp->left;
        }
        else
        {
            temp = stack.data[stack.top - 1];
            if (temp->right == NULL || temp->right == last)
            {
                PopSqStack(&stack, &temp);
                cout << temp->data << " ";
                last = temp;
                temp = NULL;
            }
            else
            {
                temp = temp->right;
            }
        }
    }
    return;
}
int main()
{
    BiTNodeIntPointer tree;
    CreateBiTNode(tree);
    PrintBiTNodeWithPost(*tree);
    return 0;
}
// 本题为6.50的代码，三元组序列创建二叉链表
#include "../DataStructure/BiTNode.h"
#include "../DataStructure/SqQueue.h"
int main()
{
    BiTNodeCharPointer tree;
    SqQueue<BiTNodeCharPointer> qu;
    InitSqQueue(qu);
    char input[MAXSIZE][3];
    int length = 0; // 记录输入数据的次数
    while (cin >> input[length][0] >> input[length][1] >> input[length][2])
    {
        if (input[length][0] == '^' && input[length][1] == '^')
            break;
        length++;
    }
    tree = new BiTNodeChar;
    tree->data = input[0][1];
    BiTNodeCharPointer temp;
    PushSqQueue(qu, tree);
    int count = 1; // 从头遍历一遍length
    while (qu.size != 0)
    {
        int quNum = qu.size-1; // 二叉树该层的节点数
        PopSqQueue(qu, &temp); // temp是上一层的节点
        while (quNum >=0)
        {
            if (temp->data == input[count][0])
            {
                if (input[count][2] == 'L')
                {
                    temp->left = new BiTNodeChar;
                    temp->left->data = input[count][1];
                    PushSqQueue(qu, temp->left);
                }
                else if (input[count][2] == 'R')
                {
                    temp->right = new BiTNodeChar;
                    temp->right->data = input[count][1];
                    PushSqQueue(qu, temp->right);
                }
                count++;
            }
            else
            {
                quNum--;
                if(quNum>=0)
                {
                    PopSqQueue(qu, &temp);
                }
            }
        }
    }
    PrintBiTNodeWithPre(*tree);
    return 0;
}
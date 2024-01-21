// 本题为3.31的代码, 用栈和队列判断字符串是否为回文
#include "../DataStructure/SqStack.h"
#include "../DataStructure/SqQueue.h"
int main()
{
    SqStackChar S;
    InitSqStack(&S);
    SqQueue<char> Q;
    InitSqQueue(Q);
    cout << "请输入字符串："<<endl;
    char temp[100];
    cin >> temp;
    //判断字符串长度是否超出数组长度
    int length = 0;
    while (temp[length] != '@')
    {
        length++;
    }
    if (length > 100)
    {
        cout << "字符串长度超出数组长度！" << endl;
        return 0;
    }
    for (int i = 0; i < length;i++)
    {
        PushSqQueue(Q, temp[i]);
        PushSqStack(&S, temp[i]);
    }
    char temp1, temp2;
    for (int i = 0; i < length;i++)
    {
        PopSqQueue(Q, &temp1);
        PopSqStack(&S, &temp2);
        if (temp1 != temp2)
        {
            cout << "不是回文！" << endl;
            return 0;
        }
    }
    cout << "是回文！" << endl;
}
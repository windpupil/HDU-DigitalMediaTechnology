//本题为3.17的代码
#include "../DataStructure/SqStack.h"
int main()
{
    SqStackChar S;
    InitSqStack(&S);
    bool isMiddle = false;
    bool isOK = true;
    while (1)
    {
        cout << "请输入元素：";
        char temp;
        cin >> temp;
        if (temp == '@')
        {
            break;
        }
        else if (temp == '&')
        {
            isMiddle = true;
        }
        else if(isMiddle==true)
        {
            char PopTemp;
            PopSqStack(&S, &PopTemp);
            if (temp != PopTemp)
            {
                isOK = false;
            }
        }
        else
        {
            PushSqStack(&S, temp);
        }
    }
    if (isOK)
    {
        cout << "输入符合题意！" << endl;
    }
    else
    {
        cout << "输入不符合题意！" << endl;
    }
}
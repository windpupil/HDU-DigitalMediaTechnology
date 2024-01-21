// 本题为3.25的代码
#include "../DataStructure/SqStack.h"
// 常规递归方法
//  int Recursion(int n)
//  {
//      if(n==0)
//      {
//          return 1;
//      }
//      else if(n>0)
//      {
//          return Recursion(n/2) *n;
//      }
//      else
//      {
//          cout << "输入不符合题意！" << endl;
//          return 0;
//      }
//  }
//  int main()
//  {
//      int temp = Recursion(4);
//      cout << temp << endl;
//  }
// 栈方法
int RecursionInStack(int n, SqStackIntPointer S)
{
    if (n < 0)
    {
        cout << "输入不符合题意！" << endl;
        return 0;
    }
    else
    {
        int temp=1;
        if (n == 0)
        {
            return 1;
        }
        while (n > 0)
        {
            PushSqStack(S, n);
            n /= 2;
        }
        while (S->top != 0)
        {
            PopSqStack(S, &n);
            temp *= n;
        }
        return temp;
    }
    return 0;
}
int main()
{
    SqStackInt S;
    InitSqStack(&S);
    int temp = RecursionInStack(4, &S);
    cout << temp << endl;
}
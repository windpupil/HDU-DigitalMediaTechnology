// 本题为3.24的代码
#include "../DataStructure/SqStack.h"
// 常规递归方法
//  int Recursion(int m,int n)
//  {
//      if(m==0&&n>=0)
//      {
//          return 0;
//      }
//      else if(m>0&&n>=0)
//      {
//          return Recursion(m - 1, n*2) + n;
//      }
//      else
//      {
//          cout << "输入不符合题意！" << endl;
//          return 0;
//      }
//  }
//  int main()
//  {
//      int temp = Recursion(5, 2);
//      cout << temp << endl;
//  }
// 栈方法
int RecursionInStack(int m, int n, SqStackIntPointer S)
{
    if (m < 0 || n < 0)
    {
        cout << "输入不符合题意！" << endl;
        return 0;
    }
    else
    {
        int temp;
        if (m == 0 && n >= 0)
        {
            return 0;
        }
        while (m > 0 && n >= 0)
        {
            PushSqStack(S, m);
            PushSqStack(S, n);
            m--;
            n *= 2;
        }
        while (S->top != 0)
        {
            PopSqStack(S, &n);
            PopSqStack(S, &m);
            temp += n;
            m--;
            n *= 2;
        }
        return temp;
    }
    return 0;
}
int main()
{
    SqStackInt S;
    InitSqStack(&S);
    int temp = RecursionInStack(5, 2, &S);
    cout << temp << endl;
}
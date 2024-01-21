// 本题为3.27的代码，实现阿克曼函数
#include "../DataStructure/SqStack.h"
// 常规递归方法
// int Ackerman(int m,int n)
// {
//     if(m==0)
//         return n+1;
//     else if(n==0)
//         return Ackerman(m-1,1);
//     else
//         return Ackerman(m-1,Ackerman(m,n-1));
// }
// int main()
// {
//     int m,n;
//     cout<<"请输入m,n的值：";
//     cin>>m>>n;
//     cout<<"Ackerman("<<m<<","<<n<<")="<<Ackerman(m,n)<<endl;
//     return 0;
// }

// 拆解递归
// 参考：https://blog.csdn.net/weixin_43717603/article/details/101174169
//基本已经是照着写了，实在想不出来。代码基本已经看懂，但是碰到这样的题时建立模型的思维还是不够
int AckermanInStack(int m, int n)
{
    SqStackInt M, N;
    InitSqStack(&M);
    InitSqStack(&N);
    PushSqStack(&M, m);
    PushSqStack(&N, n);
    while (M.top != 0)
    {
        while (m != 0)//当m不为0时，不断入栈，直至m为0时
        {
            //此处对应阿克曼函数的后两个if
            if (n == 0)
            {
                PushSqStack(&M, --m);
                PushSqStack(&N, 1);
                n = 1;
            }
            else
            {
                PushSqStack(&M, m-1);
                PushSqStack(&N, -1); //-1作为标记
                n--;
            }
        }
        n++;//n已经不是题目输入的n了，是每次n=-1时（即每个有嵌套的Ackerman函数）的n
        while (M.top != 0 && N.data[N.top - 1] != -1)//将每两个n=-1之间的过程（栈元素）出栈，这些过程的意义即为n+1
        {
            M.top--;
            N.top--;
        }
        if (M.top != 0)
        {
            //将M栈顶的元素作为新的m，取出N栈顶的-1，将现在的n入栈。
            m = M.data[M.top - 1];
            N.top--;
            PushSqStack(&N, n);
        }
    }
    return n;
}
int main()
{
    int m, n;
    cout << "请输入m,n的值：";
    cin >> m >> n;
    cout << "Ackerman(" << m << "," << n << ")=" << AckermanInStack(m, n) << endl;
    return 0;
}

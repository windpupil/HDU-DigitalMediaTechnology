// 本代码实现表达式求值的功能
#include <iostream>
#include <string>
using namespace std;
#include "../DataStructure/SqStack.h"
int Operate(int a, char symbol, int b)
{
    if (symbol == '+')
        return a + b;
    else if (symbol == '-')
        return a - b;
    else if (symbol == '*')
        return a * b;
    else if (symbol == '/')
        return a / b;
    return 0;
}
// 判断运算符的优先级
char Precede(char a, char b)
{
    if (a == '+' || a == '-')
    {
        if (b == '+' || b == '-' || b == '>' || b == '#' || b == ')' || b == ']')
            return '>';
        else
            return '<';
    }
    if (a == '*' || a == '/')
    {
        if (b == '(' || b == '[')
            return '<';
        else
            return '>';
    }
    if (a == '(')
    {
        if (b == ')')
            return '=';
        else
            return '<';
    }
    if (a == '[')
    {
        if (b == ']')
            return '=';
        else
            return '<';
    }
    if (a == '#')
    {
        if (b == '#')
            return '=';
        else
            return '<';
    }
    return 0;
}
// 表达式求值
int Evaluation(string str)
{
    SqStackChar symbol;
    SqStackInt number;
    InitSqStack(&symbol);
    InitSqStack(&number);
    PushSqStack(&symbol, '#');
    int i = 0;
    char c = str[i];
    while (c != '#' || symbol.data[symbol.top - 1] != '#')
    {
        if (c >= '0' && c <= '9')
        {
            int temp = 0;
            while (c >= '0' && c <= '9')
            {
                temp = temp * 10 + c - '0';
                i++;
                c = str[i];
            }
            PushSqStack(&number, temp);
        }
        else
        {
            if (Precede(symbol.data[symbol.top - 1], c) == '<')
            {
                PushSqStack(&symbol, c);
                i++;
                c = str[i];
            }
            else if (Precede(symbol.data[symbol.top - 1], c) == '=')
            {
                PopSqStack(&symbol, &c);
                i++;
                c = str[i];
            }
            else if (Precede(symbol.data[symbol.top - 1], c) == '>')
            {
                char symbolTemp;
                PopSqStack(&symbol, &symbolTemp);
                int b;
                PopSqStack(&number, &b);
                int a;
                PopSqStack(&number, &a);
                PushSqStack(&number, Operate(a, symbolTemp, b));
            }
        }
    }
    int result;
    PopSqStack(&number, &result);
    return result;
}
int main()
{
    string str;
    cout << "请输入表达式：" << endl;
    cin >> str;
    cout << "表达式的值为：" << Evaluation(str) << endl;
    return 0;
}
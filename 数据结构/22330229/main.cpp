#include "./ManageInformation.h"
#include "./Menu.h"
int main()
{
    ReadFile();
    InitializeTempID();
    //如何将其本地存储而非每次生成？
    while (true)
    {
        Menu(BuildAdjTable());
    }
    return 0;
}
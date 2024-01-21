// 本题为6.33的代码，判断节点u是否是节点v的子孙
#include <iostream>
using namespace std;
bool isSon(int u, int v, int L[], int R[])
{
    if(v==0)
    {
        return false;
    }
    else if(v==u)
    {
        return true;
    }
    else
    {
        return isSon(u, L[v], L, R) || isSon(u, R[v], L, R);
    }
}
int main()
{
    int n = 0;
    cout<<"请输入节点数：";
    cin>>n;
    int L[n+1]={0}, R[n+1]={0}; 
    cout<<"请输入每个节点的左右孩子：";
    for(int i=1; i<=n; i++)
        cin>>L[i]>>R[i];
    int u = 0, v = 0;
    cout<<"请输入要判断是否是子孙的节点u：";
    cin>>u;
    cout<<"请输入要判断是否是祖宗的节点v：";
    cin>>v;
    if(isSon(u, v, L, R))
    {
        cout<<"节点"<<u<<"是节点"<<v<<"的子孙"<<endl;
    }
    else
    {
        cout<<"节点"<<u<<"不是节点"<<v<<"的子孙"<<endl;
    }
}
// 本题为6.34的代码，判断节点u是否是节点v的子孙
#include <iostream>
using namespace std;
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
    int T[n+1]={0};
    for(int i=1; i<=n; i++)
    {
        if(L[i]!=0)
        {
            T[L[i]]=i;
        }
        if(R[i]!=0)
        {
            T[R[i]]=i;
        }
    }
    int temp = u;
    while(T[temp]!=0)
    {
        if (T[temp] == v)
        {
            cout << "节点" << u << "是节点" << v << "的子孙" << endl;
            return 0;
        }
        temp=T[temp];
    }
    cout<<"节点"<<u<<"不是节点"<<v<<"的子孙"<<endl;
}
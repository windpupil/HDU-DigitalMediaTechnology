//9.26的代码，实现将对分查找用递归的方式实现；
#include <iostream>
using namespace std;
#define MAXSIZE 100
int BinarySearch(int *table, int key, int left, int right)
{
    if (left > right)
    {
        return -1;
    }
    int mid = (left + right) / 2;
    if (table[mid] == key)
    {
        return mid;
    }
    else if (table[mid] > key)
    {
        return BinarySearch(table, key, left, mid - 1);
    }
    else
    {
        return BinarySearch(table, key, mid + 1, right);
    }
}
int main()
{
    int table[10] = {0,10,21,32,44,57,65,71,84,90};

    // cout<<"请输入数组长度："<<endl;
    // int length;
    // cin>>length;
    // int table[length];
    // cout<<"请输入数组："<<endl;
    // for(int i=0;i<length;i++)
    // {
    //     cin>>table[i];
    // }

    cout<<"请输入要查找的数："<<endl;
    int key;
    cin>>key;
    // int result=BinarySearch(table,key,0,length-1);
    int result = BinarySearch(table, key, 0, 9);
    if(result==-1)
    {
        cout<<"未找到"<<endl;
    }
    else
    {
        cout<<"找到了，下标为："<<result<<endl;
    }
    return 0;
}
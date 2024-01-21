//实现堆排序
#include <iostream>
using namespace std;
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
//构造大根堆,向上调整
void HeapInsert(int *array, int i)
{
    int temp = array[i];
    while (i > 0 && temp > array[(i - 1) / 2])
    {
        array[i] = array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    array[i] = temp;
}
//调整大根堆，向下
void HeapAdjust(int *array, int begin, int end)
{
    int temp = array[begin];
    int child = 2 * begin + 1;
    while (child < end)
    {
        if ((child + 1) < end && array[child + 1] > array[child])
            child++;
        if (array[child] <= temp)
            break;
        array[begin] = array[child];
        begin = child;
        child = 2 * begin + 1;
    }
    array[begin] = temp;
}
void HeapSort(int *array, int length)
{
    for (int i = 0; i < length; i++)
        HeapInsert(array, i);
    for (int i = length - 1; i > 0; i--)
    {
        swap(array[0], array[i]);
        HeapAdjust(array, 0, i);
    }
}
int main()
{
    int array[10] = {12, 5, 5, 76, 95, 24, 4, 60, -4, 10};
    HeapSort(array, 10);
    cout << "堆排序结果：";
    for (int i = 0; i < 10; i++)
        cout << array[i] << " ";
    return 0;
}
//实现快速排序
#include <iostream>
using namespace std;
void QuickSort(int *array, int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = right;
    int key = array[left];
    while (i < j)
    {
        while (i < j && array[j] >= key)
            j--;
        array[i] = array[j];
        while (i < j && array[i] <= key)
            i++;
        array[j] = array[i];
    }
    array[i] = key;
    QuickSort(array, left, i - 1);
    QuickSort(array, i + 1, right);
}
int main()
{
    int array[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    QuickSort(array, 0, 9);
    cout << "快速排序结果：";
    for (int i = 0; i < 10; i++)
        cout << array[i] << " ";
    return 0;
}
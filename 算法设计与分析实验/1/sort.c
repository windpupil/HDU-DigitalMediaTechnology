#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10
void QuickSort(int a[], int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = right, key = a[left];
    while (i < j)
    {
        while (i < j && a[j] >= key)
            j--;
        a[i] = a[j];
        while (i < j && a[i] <= key)
            i++;
        a[j] = a[i];
    }
    a[i] = key;
    QuickSort(a, left, i - 1);
    QuickSort(a, i + 1, right);
}
void Merge(int a[], int left, int mid, int right)
{
    int *temp = (int *)malloc((right - left + 1) * sizeof(int));
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= right)
        temp[k++] = a[j++];
    for (i = 0; i < k; i++)
        a[left + i] = temp[i];
    free(temp);
}
void MergeSort(int a[], int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    MergeSort(a, left, mid);
    MergeSort(a, mid + 1, right);
    Merge(a, left, mid, right);
}
void BubbleSort(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}
void InsertSort(int a[], int n)
{
    int i, j, temp;
    for (i = 1; i < n; i++)
    {
        temp = a[i];
        for (j = i; j > 0 && a[j - 1] > temp; j--)
            a[j] = a[j - 1];
        a[j] = temp;
    }
}
void SelectSort(int a[], int n)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[min])
                min = j;
        }
        if (min != i)
        {
            temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}
int main()
{
    int a[SIZE], i;
    srand(time(NULL));
    for (i = 0; i < SIZE; i++)
        a[i] = rand() % 100;
    for (i = 0; i < SIZE; i++)
        printf("%d ", a[i]);
    printf("\n");
    BubbleSort(a, SIZE);
    // InsertSort(a, SIZE);
    // SelectSort(a, SIZE);
    // QuickSort(a, 0, SIZE - 1);
    // MergeSort(a, 0, SIZE - 1);
    for (i = 0; i < SIZE; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
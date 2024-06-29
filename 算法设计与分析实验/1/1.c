#include <stdio.h>
int main()
{
    int n, i, j, k, a[10] = {0};
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        j = i;
        while (j > 0)
        {
            k = j % 10;
            a[k]++;
            j /= 10;
        }
    }
    for (i = 0; i < 10; i++)
    {
        printf("有%d个%d ", a[i],i);
    }
    return 0;
}
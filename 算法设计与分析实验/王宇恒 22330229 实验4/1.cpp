#include <stdio.h>
void Swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

void Perm(int *br, int k, int m)
{
    if (k == m)
    {
        for (int i = 0; i <= m; ++i)
        {
            printf("%d ", br[i]);
        }
        printf("\n");
    }
    else
    {
        for (int j = k; j <= m; ++j)
        {
            Swap(br[j], br[k]);
            Perm(br, k + 1, m);
            Swap(br[j], br[k]);
        }
    }
}

int main()
{
    int ar[] = {1, 2};
    // int ar[] = {1, 2, 3};
    // int ar[]={1,2,3,4};
    int n = sizeof(ar) / sizeof(ar[0]);
    Perm(ar, 0, n - 1);
    return 0;
}
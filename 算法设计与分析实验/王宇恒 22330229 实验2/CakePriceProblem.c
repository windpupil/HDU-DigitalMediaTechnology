#include <stdio.h>

int maxCakePrice(int weight[], int price[], int tw, int n)
{
    int dp[21][200] = {0};
    for (int i = 1; i <= n; ++i)
    {
        for (int w = 1; w <= tw; ++w)
        {
            if (weight[i - 1] <= w)
            {
                dp[i][w] = (dp[i - 1][w] > dp[i - 1][w - weight[i - 1]] + price[i - 1]) ? dp[i - 1][w] : dp[i - 1][w - weight[i - 1]] + price[i - 1];
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][tw];
}

int main()
{
    int num;
    printf("请输入蛋糕种类数：\n");
    scanf("%d", &num);
    printf("\n");
    int tw;
    printf("请输入背包容量：\n");
    scanf("%d", &tw);
    printf("\n");
    int weight[20] = {0};
    int price[20] = {0};
    for (int i = 0; i < num; i++)
    {
        printf("请输入第%d种蛋糕的价格和重量：\n", i + 1);
        scanf("%d %d", &price[i], &weight[i]);
        printf("\n");
    }
    int maxPrice = maxCakePrice(weight, price, tw, num);
    printf("最大价值为：%d\n", maxPrice);
    return 0;
}

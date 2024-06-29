#include <stdio.h>

int f[100][100]; // 状态函数f[i][j]表示第i件物品容量为j最大价值
int v[100];     // 物品价值
int w[100];     // 物品重量

int max(int a, int b) {
    return (a > b) ? a : b;
}

int fun(int n, int m) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j < w[i])
                f[i][j] = f[i - 1][j];
            else
                f[i][j] = max(f[i - 1][j], f[i - 1][j - w[i]] + v[i]);
        }
    }
    return f[n][m];
}

int main() {
    int n, m; // n:物品数量 m:背包容量
    printf("请输入物品数量和背包容量\n");
    scanf("%d %d", &n, &m);
    printf("请输入物品的重量和价值\n");
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &w[i], &v[i]);
    printf("结果为 %d\n", fun(n, m));
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void LCSLength(int m, int n, char *x, char *y, int **dp, int **b)
{
	int i, j;
	dp[0][0] = 0;
	for (i = 1; i <= m; i++)
		dp[i][0] = 0;
	for (i = 1; i <= n; i++)
		dp[0][i] = 0;
	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++)
			if (x[i - 1] == y[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
				b[i][j] = 1;
			}
			else if (dp[i - 1][j] >= dp[i][j - 1])
			{
				dp[i][j] = dp[i - 1][j];
				b[i][j] = 3;
			}
			else
			{
				dp[i][j] = dp[i][j - 1];
				b[i][j] = 2;
			}
}
void LCS(int i, int j, char *x, int **b)
{
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 1)
	{
		LCS(i - 1, j - 1, x, b);
		printf("%c", x[i - 1]);
	}
	else if (b[i][j] == 3)
		LCS(i - 1, j, x, b);
	else
		LCS(i, j - 1, x, b);
}
int main()
{
	char x[100], y[100];
	printf("请输入字符串X：\n");
	scanf("%s", x);
	printf("请输入字符串Y：\n");
	scanf("%s", y);
	int m = strlen(x);
	int n = strlen(y);
	int **dp = (int **)malloc((m + 1) * sizeof(int *));
	int **b = (int **)malloc((m + 1) * sizeof(int *));
	for (int i = 0; i <= m; i++)
	{
		dp[i] = (int *)malloc((n + 1) * sizeof(int));
		b[i] = (int *)malloc((n + 1) * sizeof(int));
	}
	LCSLength(m, n, x, y, dp, b);
	printf("最长公共子序列为：");
	LCS(m, n, x, b);
	printf("\n");
	printf("最长公共子序列的长度为：%d\n", dp[m][n]);
	return 0;
}
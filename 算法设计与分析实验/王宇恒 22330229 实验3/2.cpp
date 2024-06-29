#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define INF 0x3f3f3f3f
using namespace std;
const int maxn = 505;
int a[maxn][maxn];//邻接矩阵
int vis[maxn], dist[maxn];//vis数组标记是否访问过，dist数组记录当前点到最小生成树的距离
int n, m;//n个点，m条边
int u, v, w;//u,v为边的起点和终点，w为边的权重
long long sum = 0;
int prim(int pos)//pos为起点
{
    dist[pos] = 0;
    for (int i = 1; i <= n; i++)
    {
        int cur = -1;
        for (int j = 1; j <= n; j++)
        {
            if (!vis[j] && (cur == -1 || dist[j] < dist[cur]))
            {
                cur = j;
            }
        }
        if (dist[cur] >= INF)
            return INF;
        sum += dist[cur];
        vis[cur] = 1;
        for (int k = 1; k <= n; k++)
        {
            if (!vis[k])
                dist[k] = min(dist[k], a[cur][k]);
        }
    }
    return sum;
}

int main(void)
{
    cout<<"请输入点的个数和边的个数："<<endl;
    cin >> n >> m;
    memset(a, 0x3f, sizeof(a));
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 1; i <= m; i++)
    {
        cout << "请输入边的起点、终点和权重：" << endl;
        cin >> u >> v >> w;
        a[u][v] = min(a[u][v], w);
        a[v][u] = min(a[v][u], w);
    }
    int value = prim(1);
    if (value >= INF)
        cout << "impossible" << endl;
    else
        cout << value << endl;
    return 0;
}
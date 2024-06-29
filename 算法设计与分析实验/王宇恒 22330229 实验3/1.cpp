#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;
int main()
{
    int n, m;
    // cout<<"请输入点的个数和边的个数："<<endl;
    // cin >> n >> m;
    #pragma region 例子1
    n = 6;
    m = 9;
    #pragma endregion
    vector<pair<int, int>> points(n);
    #pragma region 例子1
    points[0] = make_pair(1000, 2400);
    points[1] = make_pair(2800, 3000);
    points[2] = make_pair(2400, 2500);
    points[3] = make_pair(4000, 0);
    points[4] = make_pair(4500, 3800);
    points[5] = make_pair(6000, 1500);
    #pragma endregion
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> points[i].first >> points[i].second;
    // }
    vector<vector<int>> graph(n, vector<int>(n, INT_MAX));
    #pragma region 例子1
    graph[0][1] = graph[1][0] = sqrt(pow(points[0].first - points[1].first, 2) + pow(points[0].second - points[1].second, 2));
    graph[0][3] = graph[3][0] = sqrt(pow(points[0].first - points[3].first, 2) + pow(points[0].second - points[3].second, 2));
    graph[1][2] = graph[2][1] = sqrt(pow(points[1].first - points[2].first, 2) + pow(points[1].second - points[2].second, 2));
    graph[1][4] = graph[4][1] = sqrt(pow(points[1].first - points[4].first, 2) + pow(points[1].second - points[4].second, 2));
    graph[2][4] = graph[4][2] = sqrt(pow(points[2].first - points[4].first, 2) + pow(points[2].second - points[4].second, 2));
    graph[2][3] = graph[3][2] = sqrt(pow(points[2].first - points[3].first, 2) + pow(points[2].second - points[3].second, 2));
    graph[2][5] = graph[5][2] = sqrt(pow(points[2].first - points[5].first, 2) + pow(points[2].second - points[5].second, 2));
    graph[3][5] = graph[5][3] = sqrt(pow(points[3].first - points[5].first, 2) + pow(points[3].second - points[5].second, 2));
    graph[4][5] = graph[5][4] = sqrt(pow(points[4].first - points[5].first, 2) + pow(points[4].second - points[5].second, 2));
    #pragma endregion
    // for (int i = 0; i < m; i++)
    // {
    //     int a, b;
    //     cin >> a >> b;
    //     graph[a][b] = graph[b][a] = sqrt(pow(points[a].first - points[b].first, 2) + pow(points[a].second - points[b].second, 2));
    // }
    int source, target;
    // cin >> source >> target;
    #pragma region 例子1
    source = 1;
    target = 1;
    #pragma endregion
    vector<int> dist(n, INT_MAX);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);
    dist[source] = 0;
    for (int i = 0; i < n; i++)
    {
        int u = -1;
        int minDist = INT_MAX;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && dist[j] < minDist)
            {
                u = j;
                minDist = dist[j];
            }
        }
        if (u == -1)
        {
            break;
        }
        visited[u] = true;
        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && graph[u][v] != INT_MAX)
            {
                if (dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                    prev[v] = u;
                }
            }
        }
    }
    cout << "最短路径长度为：" << dist[target] << endl;
    cout << "最短路径为：";
    vector<int> path;
    for (int i = target; i != -1; i = prev[i])
    {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i] << " ";
    }
}
#include <iostream>
#include <cstring>

#define x first
#define y second
using namespace std;

typedef pair<int, int> PII;
const int N = 155, M = N * N;

int n, m;
char g[N][N];
PII q[M];
int dist[N][N];


int bfs()
{
    int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

    int sx, sy;
    for (int i = 0; i < n; ++ i )   
        for (int j = 0; j < m; ++ j )
            if (g[i][j] == 'K') sx = i, sy = j;     // 找到起点

    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    memset(dist, -1, sizeof dist);      // 遍历过的点不需要再遍历
    dist[sx][sy] = 0;

    while (hh <= tt)
    {
        auto t = q[hh ++ ];
        // 枚举一个点, 所有可扩展出的 8 个方向
        for (int i = 0; i < 8; ++ i )
        {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= m) continue;   // 越界
            if (g[a][b] == '*') continue;       // 障碍
            if (dist[a][b] != -1) continue;     // 枚举过
            if (g[a][b] == 'H') return dist[t.x][t.y] + 1;  // 终点找到了, 之前的步骤数 + 1 
            
            dist[a][b] = dist[t.x][t.y] + 1;
            q[ ++ tt] = {a, b};
        }
    }
    return -1;
}

int main()
{
    scanf("%d%d", &m, &n);
    for (int i = 0; i < n; ++ i ) cin >> g[i];
    cout << bfs() << endl;
    return 0;
}

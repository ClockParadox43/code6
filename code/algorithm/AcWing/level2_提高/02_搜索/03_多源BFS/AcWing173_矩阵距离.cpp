// 两个坐标之间的曼哈顿距离:dist(g[i][j], g[k][l]) = |i-k| + |j-l|
// 求每个位置到所有 1 的最短距离, 1 到所有点的距离是 0, 所以 1 是 0, 
// 这个距离就是曼哈顿距离
// 朴素解法: 分别以每个 1 为起点, 然后保留最小值
//          参考图论求最短路有到最近起点的最短距离(和多源最短路不一样, 多源最短路求的是两点之间的最短距离)
//          可以转化成单源最短路:建立一个虚拟源点, 用虚拟源点向每个起点连一条边权为 0 的边
//          从每个点到最近真实起点的距离的距离可以看这个点到虚拟源点的最近的距离
//          因为从虚拟源点求最短路会考虑每一个分支, 最终考虑最近的那个分支

#include <iostream>
#include <cstring>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 1010, M = N * N;

int n, m;
char g[N][N];
PII q[M];
int dist[N][N];

void bfs()
{
    memset(dist, -1, sizeof dist);
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    int hh = 0, tt = -1;
    for (int i  = 1; i <= n; ++ i )         // 将 1 作为起点加入队列
        for (int j = 1; j <= m; ++ j )
            if (g[i][j] == '1')
            {
                dist[i][j] = 0;
                q[ ++ tt] = {i, j};
            }

    while (hh <= tt)
    {
        auto t = q[hh ++ ];
        for (int i = 0; i < 4; ++ i )
        {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 1 || a > n || b < 1 || b > m) continue;     // 处理越界
            if (dist[a][b] != -1) continue;     // 遍历过的点
            dist[a][b] = dist[t.x][t.y] + 1;    
            q[ ++ tt] = {a, b}; 
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i ) scanf("%s", g[i] + 1);
    
    bfs();
    
    for (int i = 1; i <= n; ++ i )
    {
        for (int j = 1; j <= m; ++ j ) printf("%d ", dist[i][j]);
        puts("");
    }
    return 0;
}
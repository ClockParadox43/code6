// 最短路模型:当所有边权重都是相等的时候, 用宽搜从起点开始搜
//            找到的第一条路就是单元最短路
#include <iostream>
#include <cstring>

#define x first
#define y second
using namespace std;

typedef pair<int, int> PII;
const int N = 1010;
int n;
int g[N][N]
PII q[N * N];       // 宽搜
PII pre[N][N];      // 记录每个格子是从哪个格子反推出来的, 这样自底倒退出最短路径

void bfs(int sx, int sy)
{
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
    
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    memset(pre, -1, sizeof pre);
    pre[sx][sy] = {0, 0};           // 起点是唯一的, 一定是 {0,0}, {0,0} 中存的是那个点就看谁先到的{0,0}
    
    while (hh <= tt)
    {
        PII t = q[hh ++ ];
        for (int i = 0; i < 4; ++ i )
        {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a >= n || b < 0 && b >= n) continue;
            if (g[a][b]) continue;
            if (pre[a][b].x != -1) continue;        // 如果当前点等于 -1, 说明这个点遍历过了

            q[ ++ tt] = {a, b};     // 当前路径
            pre[a][b] = t;          // 记录当前路径的上一条路径, 当前路劲的上一条路径是 t 
        }                           // 比如当前路径是 pre[3][4], 那么它的上一条路径就是 t(4,4)
    }                               // 也就是 pre[3][4] = t{4,4}
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i )
        for (int j = 0; j < n; ++ j )
            scanf("%d", &g[i][j]);

    // 反向搜:因为正向搜终点为[n-1,n-1], 从[n-1,n-1]开始, 打印的迷宫顺序是反着的
    // 所以这里采取反向搜
    bfs(n - 1, n - 1);
    // PII end(0, 0);
    PII end = {0 , 0};
    while (true)
    {
        printf("%d %d\n", end.x, end.y);
        if (end.x == n - 1 && end.y == n - 1) break;
        end = pre[end.x][end.y];
    }
    return 0;
}
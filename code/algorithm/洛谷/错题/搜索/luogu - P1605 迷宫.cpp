
// 问题: 走到终点的方案数

#include <iostream>

using namespace std;
typedef long long ll;
const int MAXN = 15;

// 深搜就是不撞南墙不回头然后回到前层
int n, m, sx, sy, tx, ty, t, ans;
char g[MAXN][MAXN];
bool st[MAXN][MAXN];
int walk[4][4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

void dfs(int x, int y)
{
    // 第一我们要考虑的是 dfs 是否已经到终点了
    if (g[x][y] == 'T') { ans++; return; }

    for (int i = 0; i < 4; ++ i)
    {
        int dx = x + walk[i][0], dy = y + walk[i][1];
        if (dx < 1 || dx > n || dy < 1 || dy > m || g[dx][dy] == '#') continue;
        if (st[dx][dy]) continue;
        st[dx][dy] = true;
        dfs(dx, dy);
        st[dx][dy] = false;
    }
}

int main()
{
    cin >> n >> m >> t;             // n * m 的矩阵, t 个障碍物
    cin >> sx >> sy >> tx >> ty;    // 起点, 终点
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            g[i][j] = '.';

    g[tx][ty] = 'T';
    // 读入障碍物
    for (int i = 1; i <= t; ++ i)
    {
        int x, y; cin >> x >> y;
        g[x][y] = '#';
    }

    st[sx][sy] = true;
    dfs(sx, sy);
    cout << ans << endl;
    return 0;
}
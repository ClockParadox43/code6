
// 问题: 求最短路

#include <iostream>
#include <queue>
#include <cstring>

#define fs first
#define sc second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 250, INF = 0x3f3f3f3f;

// 深搜就是不撞南墙不回头然后回到前层
int n, m, sx, sy, tx, ty, t, ans = INF;
char g[MAXN][MAXN];
int d[MAXN][MAXN];
bool st[MAXN][MAXN];
int walk[4][4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

void bfs()
{
    queue<pii> q; q.push({ sx, sy });
    memset(d, 0x3f, sizeof d);      // 63:0x3f
    d[sx][sy] = 0, st[sx][sy] = true;
    
    while (q.size())
    {
        auto t = q.front(); q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int dx = t.fs + walk[i][0], dy = t.sc + walk[i][1];
            if (dx < 1 || dx > n || dy < 1 || dy > m || st[dx][dy] || g[dx][dy] == '#') continue;

            st[dx][dy] = true;
            q.push({ dx, dy });
            d[dx][dy] = d[t.fs][t.sc] + 1;

            // 特判, 就算把特判注释掉结果始终不变, 因为整张图只会走一次, 加上特判可以提前退出
            if (dx == tx && dy == ty) return;
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            cin >> g[i][j];
            if (g[i][j] == 'S')
                sx = i, sy = j;
            else if (g[i][j] == 'T')
                tx = i, ty = j;

        }

    st[sx][sy] = true;
    bfs();
    if (d[tx][ty] != INF) cout << d[tx][ty];
    else cout << -1;
    return 0;
}
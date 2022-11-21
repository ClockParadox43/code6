#include <iostream>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;     
const int N = 1010, M = N * N;

int n, m;
char g[N][N];
PII q[M];       // 因为是二维, 所以下标就要存两维
bool st[N][N];  // 宽搜基本都需要判断重复

void bfs(int sx, int sy)
{
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    st[sx][sy] = true;      // 标记就是为了减少重复遍历, 防止时间复杂度变成指数级别
    
    while (hh <= tt)
    {
        PII t = q[hh ++ ];
        // 只看周围 8 个格子
        for (int i = t.x - 1; i <= t.x + 1; ++ i )
            for (int j = t.y - 1; j <= t.y + 1; ++ j )
            {
                if (i == t.x && j == t.y) continue;               // 自己不用看, 看自己周围的格子就行
                if (i < 0 || i >= n || j < 0 || j >= m) continue; // 越界情况
                if (g[i][j] == '.' || st[i][j]) continue;         // 遍历过或者不是水的情况
                q[ ++ tt] = {i, j};                               // 有水的格子全部进了队列
                st[i][j] = true;
            }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i ) scanf("%s", g[i]);
    
    int cnt = 0;
    for (int i = 0; i < n; ++ i )
        for (int j = 0; j < m; ++ j )
            if (g[i][j] == 'W' && !st[i][j])
                bfs(i, j), cnt ++ ;
            
    printf("%d\n",cnt);
    return 0;   
}

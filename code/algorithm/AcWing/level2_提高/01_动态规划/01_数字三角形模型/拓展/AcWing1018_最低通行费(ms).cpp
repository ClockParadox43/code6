
// 起点走到 (i,j) 最少的代价

#include <iostream>
#include <cstring>

#define MAXN 103
using namespace std;
const int INF = 0x3f3f3f3f;

int n;
int f[MAXN][MAXN];
int w[MAXN][MAXN];

// 最先返回到 (1,1)
int dp(int i, int j)
{
    if (f[i][j] >= 0) return f[i][j];
    if (i == 1 && j == 1) return w[i][j];   // 走到 dp(1,1) 必然返回(边界), 因此所有计算都是建立在 f(1,1) 上
    if (i < 1 || j < 1) return INF;         // 边界外的必然不会取

    int t = INF;
    t = min(t, dp(i - 1, j) + w[i][j]);
    t = min(t, dp(i, j - 1) + w[i][j]);
    return f[i][j] = t;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            scanf("%d", &w[i][j]);
    
    memset(f, -1, sizeof f);
    cout << dp(n, n);
    return 0;
}
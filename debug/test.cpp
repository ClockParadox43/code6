
// 起点走到 (i,j) 最少的代价

#include <iostream>
#include <cstring>

#define MAXN 103
using namespace std;
const int INF = 0x3f3f3f3f;

int n;
int f[MAXN][MAXN];
int w[MAXN][MAXN];

int dp(int i, int j)
{
    if (f[i][j] >= 0) return f[i][j];
    if (i == 1 && j == 1) return w[i][j];
    if (i < 1 || j < 1) return INF;

    int t = INF;
    t = min(t, dp(i - 1, j));
    t = min(t, dp(i, j - 1));
    return f[i][j] = t + w[i][j];
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
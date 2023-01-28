#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 55, MAXM = MAXN << 1, INF = 0x3f3f3f3f;

int n, m;
int w[MAXN][MAXN];
int f[MAXM][MAXN][MAXN];

int dp(int k, int i, int j)
{
    if (f[k][i][j] >= 0) return f[k][i][j];
    if (k == 2 && i == 1 && j == 1) return f[k][i][j] = w[1][1];    // 最初始到状态
    if (i <= 0 || i >= k || j <= 0 || j >= k) return -INF;          // 越界

    int v = w[i][k - i];
    if (i != j) v += w[j][k - j];

    int t = 0;
    t = max(t, dp(k - 1, i, j));
    t = max(t, dp(k - 1, i - 1, j));
    t = max(t, dp(k - 1, i, j - 1));
    t = max(t, dp(k - 1, i - 1, j - 1));
    return f[k][i][j] = t + v;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            cin >> w[i][j];
    
    memset(f, -1, sizeof f);
    cout << dp(n + m, n, n) << endl;
    return 0;
}



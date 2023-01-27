#include <iostream>

#define MAXN 55
using namespace std;

int n, m;
int f[MAXN][MAXN][MAXN][MAXN];
int w[MAXN][MAXN];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            scanf("%d", &w[i][j]);
    
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            for (int h = 1; h <= n; ++ h)
                for (int k = 1; k <= m; ++ k)
                {
                    // 上上, 上左, 左上, 左左
                    int t1 = max(f[i - 1][j][h - 1][k], f[i - 1][j][h][k - 1]);
                    int t2 = max(f[i][j - 1][h - 1][k], f[i][j - 1][h][k - 1]);
                    f[i][j][h][k] = max(t1, t2) + w[i][j] + w[h][k];
                    if (i == h && j == k) f[i][j][h][k] -= w[i][j];
                }
    cout << f[n][m][n][m];
    return 0;
}
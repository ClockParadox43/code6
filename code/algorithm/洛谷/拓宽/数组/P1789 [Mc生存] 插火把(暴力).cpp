#include <iostream>

using namespace std;
const int MAXN = 104;

int n, m, k;            // m:火把, k:荧石
bool g[MAXN][MAXN];
int light;

// 暴力写一遍
// 模拟写一遍
int main()
{
    scanf("%d%d%d", &n, &m, &k);

    while (m--)
    {
        // 火把如果同行同列就填写 1
        int x, y; scanf("%d%d", &x, &y);
        g[x][y] = 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
                if (i == x)
                    if (j <= y + 2 && j >= y - 2) g[i][j] = 1;
                if (j == y)
                    if (i <= x + 2 && i >= x - 2) g[i][j] = 1;
                if ((i == x + 1 && j == y + 1) || (i == x - 1 && j == y - 1) || (i == x - 1 && j == y + 1) || (i == x + 1 && j == y - 1))
                    g[i][j] = 1;
            }
    }

    while (k--)
    {
        int x, y; scanf("%d%d", &x, &y);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (i >= x - 2 && i <= x + 2 && j >= y - 2 && j <= y + 2)
                    g[i][j] = 1;
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            light += g[i][j];
    cout << n * n - light << endl;
    return 0;
}
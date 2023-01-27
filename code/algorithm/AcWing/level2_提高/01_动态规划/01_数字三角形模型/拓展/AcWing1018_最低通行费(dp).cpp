
// 错误方程转移: f[i][j] = min(f[i - 1][j] + w[i][j], f[i][j - 1] + w[i][j])
// 因为 f[i-1][j] 和 f[i][j-1] 都在边界外, 也就是 INF, 所以求到的当然是 INF
// 
// 正确的转态转移 初始化 f[1][1]
//               f[i][j] = min(f[i][j], f[i - 1][j] + w[i][j])
//               f[i][j] = min(f[i][j], f[i][j + 1] + w[i][j])

#include <iostream>
#include <cstring>

#define MAXN 104
#define INF 0x3f3f3f3f
using namespace std;

int n;
int f[MAXN][MAXN];
int w[MAXN][MAXN];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            scanf("%d", &w[i][j]);

    memset(f, 0x3f, sizeof f);
    f[1][1] = w[1][1];
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
        {
            f[i][j] = min(f[i][j], f[i - 1][j] + w[i][j]);
            f[i][j] = min(f[i][j], f[i][j - 1] + w[i][j]);
        }
    
    printf("%d", f[n][n]);
    return 0;
}

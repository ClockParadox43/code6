// 用四重循环枚举两条路分别走到的位置, 由于每个点均从上或下继承而来, 故内部有四个 if, 分别
// 代表两个点 上上, 上左, 左上, 左左 继承而来, 加上当前两个点所取得的最大值. a[i,j] 表示 (i,j)
// 格上面的值, f[i,j,h,k] 表示第一条路走到(i,j), 第二条路走到 (h,k) 时的最优
// 
// 例: f[i,j,h,k] = max{f[i,j,h,k], f[i-1,j,h-1,k] + a[i,j] + a[h,k]}
// 1.当 (i,j) 大于或者小于 (h,k) 时
//      - f[i,j,h,k] = max{f[i-1,j,h-1,k], f[i,j-1,h,k-1], f[i-1,j,h,k-1], f[i,j-1,h-1,k]}+a[i,j]+a[h,k]
// 2.当(i,j) 等于 (h,k)
//      - f[i,j,h,k] = max{f[i-1,j,h-1,k], f[i,j-1,h,k-1], f[i-1,j,h,k-1], f[i,j-1,h-1,k]}+a[i,j]


#include <iostream>

#define MAXN 15
using namespace std;

int n;
int f[MAXN][MAXN][MAXN][MAXN];
int w[MAXN][MAXN];

int main()
{
    scanf("%d", &n);
    int x, y, t;
    while (cin >> x >> y >> t, x || y || t) w[x][y] = t;

    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            for (int h = 1; h <= n; ++ h)
                for (int k = 1; k <= n; ++ k)
                {
                    int t1 = max(f[i - 1][j][h - 1][k], f[i][j - 1][h][k - 1]);
                    int t2 = max(f[i - 1][j][h][k - 1], f[i][j - 1][h - 1][k]);
                    f[i][j][h][k] = max(t1, t2) + w[i][j];
                    if (i != h && j != k) f[i][j][h][k] += w[h][k];        // 如果走的路径不相同
                    // printf("f[%d][%d][%d][%d]:%d%c", i, j, h, k, f[i][j][h][k], k < n ? 0x20 : 0x0A);
                }

    cout << f[n][n][n][n];
    return 0;
    
}
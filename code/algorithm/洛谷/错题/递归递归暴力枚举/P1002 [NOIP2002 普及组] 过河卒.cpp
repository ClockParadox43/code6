#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
// 设 f[i,j] 表示从 (1,1) 格子走到当前格子的路径条数, 那么根据上一段得到的结论, 可以得到:
// f[i,j] = f[i-1,j] + f[i,j-1] -> 马可以从上面下来, 也可以从左边过来
// 
// 递推给我的感觉有点像 bfs, 因为队列的两端性, 队列中的格子只有 0 和 1
// 而递推也是用上个状态去递推出现在的状态 

using namespace std;
const int MAXN = 25;
typedef long long LL;

int bx, by, mx, my;
LL f[MAXN][MAXN];
bool st[MAXN][MAXN];
const int dx[] = { 0, -2, -1, 1, 2, 2, 1, -1, -2 };
const int dy[] = { 0, 1, 2, 2, 1, -1, -2, -2, -1 };
//马可以走到的位置

int main()
{
    scanf("%d%d%d%d", &bx, &by, &mx, &my);

    st[mx][my] = true;
    for (int i = 1; i <= 8; ++i)
        st[mx + dx[i]][my + dy[i]] = 1;

    for (int i = 0; i <= bx; ++ i)
        for (int j = 0; j <= by; ++ j)
        {
            if (st[i][j]) continue;
            if (i == 0 && j == 0) f[0][0] = 1;  // 递推边界
            else if (i == 0 && j > 0)   // x = 0 时
                f[0][j] = f[0][j - 1];
            else if (i > 0 && j == 0)   // y = 0 时
                f[i][0] = f[i - 1][0];
            else f[i][j] = f[i - 1][j] + f[i][j - 1];
        }
    printf("%lld", f[bx][by]);
    return 0;
}


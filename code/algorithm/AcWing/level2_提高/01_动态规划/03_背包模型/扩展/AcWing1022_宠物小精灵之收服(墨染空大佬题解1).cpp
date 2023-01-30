// 在背包问题中, 体积w 与 价值v 是可以互逆的!
// 可以将 f[i] 表示为体积为 i 能装的最大价值,
// 也可以将 f[i] 表示为价值为 i 所需的最小体积.
// 两者等价, 我们只需要选择范围较小的那维作为体积就可以了!
// 这直接影响到时空复杂度.
// 这题就是个案例.
// f[i][j]: 表示为体力为ii, 精灵球数为jj所收集到的最大精灵.
// 时间复杂度:5*10^7
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1003, MAXM = 505, MAXS = 103;

int n, m, K;
int w[MAXS], v[MAXS];
int f[MAXN][MAXM]; 

int main()
{
    memset(f, 0xcf, sizeof f);  // 负无穷
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 1; i <= K; ++ i)
        scanf("%d%d", w + i, v + i);    // w:球数量, v:血量
    
    f[0][0] = 0;
    for (int i = 1; i <= K; ++ i)
        for (int j = n; j >= w[i]; -- j)
            for (int k = m; k >= v[i]; -- k)
                f[j][k] = max(f[j][k], f[j - w[i]][k - v[i]] + 1);
    
    int res = -1, t;
    for (int j = 0; j <= n; ++ j)       // 球数量
        for (int k = 0; k < m; ++ k)    // 血量
            if (f[j][k] > res || (res == f[j][k] && k < t))  // 如果总价值最优秀 或者 总价值相等 且 花费血量少于临时变量
                res = f[j][k], t = k;

    printf("%d %d\n", res, m - t);
    return 0;
}


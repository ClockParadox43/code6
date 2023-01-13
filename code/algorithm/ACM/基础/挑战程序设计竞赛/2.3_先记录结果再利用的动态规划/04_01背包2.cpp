// 有 N 个重量和价值是 wi, vi 的物品, 每件物品只能使用一次
// 求解将哪些物品装入背包, 可使这些物品的总体积不超过背包容量, 且总价值最大
// 输出最大价值
// 1 ≤ n ≤ 100
// 1 ≤ wi ≤ 10^7 ★
// 1 ≤ vi ≤ 100  
// 1 ≤ W ≤ 10^9 ★


// 相比重量而言, 价值的重量较小, 所以可以试着改变 dp[i,j] 状态表示
// 编号01 是针对不同重量枚举计算最大价值, 编号04 不妨针对不同价值计算最小重量
// dp[i+1,j]: 前 i 件物品中, 挑选出价值总和为 j 时总重量的最小值
// 由于前 0 个物品挑选不了, 边界设置为 INF
//      - 前 i-1 个物品中挑选价值总和为 j 的部分
//      - 前 i-1 个物品中挑选价值总和为 j-v[i] 的部分, 然后选中第 i 个物品
//        dp[i+1,j] = min(dp[i,j], dp[i,j-v[i]]+w[i]
#include <iostream>
#include <cstring>

using namespace std;
const int MAXN = 101, MAXV = 101;

int n = 4, m = 5;
int w[4] = {2, 1, 3, 2};
int v[4] = {3, 2, 4, 2};
int dp[MAXN][MAXN * MAXV];

int main()
{
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;

    for (int i = 0; i < n; ++ i)
        for (int j = 0; j <= MAXN * MAXV; ++ j)
            if (j < v[i]) 
                dp[i + 1][j] = dp[i][j];
            else 
                dp[i + 1][j] = min(dp[i][j], dp[i - 1][j - v[i]] + w[i]);

    int res = 0;
    for (int i = 0; i <= MAXN * MAXV; ++ i ) 
        if (dp[n][i] <= m) res = i;

    printf("%d", res);

    return 0;  
}


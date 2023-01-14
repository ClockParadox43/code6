// 有 n 种不同大小的数字 ai, 每种各 mi 个, 判断是否可以从这些数字中选出若干个, 使它们的和恰好为 k 
//
// dp[i,j]:前 i 种数字是否能加和为 j
// 为了能使得前 i 种数字加和为 j, 所以需要前 i-1 种数字加和为 j, j-ai, j-mi*ai 中的某一种
// dp[i + 1][j] = dp[i][j - k * a[i]]

#include <iostream>

using namespace std;
const int MAXN = 105, MAXK = 100010;

int n = 3, K = 17;
int a[3] = {3, 5, 8};
int m[3] = {3, 2, 2};
int dp[MAXN][MAXK];

// dp[0] 选 0 个数字
// dp[1] 有 1 出现就是当前第 1 个数字选了的情况且能组成 j
// dp[i] 前 i 个数字能是否能组成当前数
// 每一层的答案迭代下来
int main()
{
    dp[0][0] = true;        // 当要求 k 为 0 时, 前 0 个数字可以组成 0 
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j <= K; ++ j)
            for (int k = 0; k * m[i] <= j && k <= m[i]; ++ k)
                dp[i + 1][j] |= dp[i][j - k * m[i]];    // 如果 i-1 能够组成 j 那么就是 true

    if (dp[n][K]) puts("Yes");
    else puts("No");

    return 0;
}

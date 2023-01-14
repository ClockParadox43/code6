// 有 n 个无区别的物品, 将它们划分成 m 组, 求出有几种划分方法, 答案取模 M
// 
// 这样的划分被称为 n 的 m 划分, 特别地, m = n 时, m 就是 n 的划分数
// dp[i][j] = j 的 i 划分总数 (枚举区间)
// 
// 考虑 n 的 m 划分(划分成 m 份等于 n), 如果对于每个 i 都有 ai > 0, 那么 {ai-1} 就对应了 n-m 的 m 的划分
// 另外, 如果 ai = 0, 那么就对应了 n 的 m-1 划分  
// dp[i][j] = dp[i][j-i] + dp[i-1][j]
//
// 例:n=6, m=4
// {6, 0006}, {15, 0015}, {25, 0024}, {36, 0036}, {114, 0114}
// {123, 0123}, {222, 0222} | {1113, 1113}, {1122, 1122}
// 总方案数有两类, 总 = 包含 0 的方案数 + 不包含 0 的方案数 
#include <iostream>
#include <cstring>

using namespace std;
const int MAXN = 1005;

int n, m, M;      // 划分 4, 每一份不超过 3 (n 的 m 划分)
int dp[MAXN][MAXN];

//dp[m][n] 表示m个数相加为n的方案数
//dp[m][n] = dp[m][n-m]+dp[m-1][n]
int main()
{
    scanf("%d%d%d", &n, &m, &M);
    dp[0][0] = 1;   //0 个数字相加为0  方案数1种
    // j 的 i 划分
    for (int i = 1; i <= m; i ++ )
		for (int j = 0; j <= n; j ++ )
        {
            // 包含 0 的方案
            dp[i][j] += dp[i - 1][j];
            // 如果 j >= i, 那么也可以划分为 i 份
            if (j >= i)
				dp[i][j] += dp[i][j - i];
             dp[i][j] %= M;
        }
    printf("%d\n", dp[m][n]);
    return 0;
}

#include <iostream>

using namespace std;
const int MAXN = 105, MAXM = 10005;

int n = 4, m = 5;
int w[4] = {2, 1, 3, 2};
int v[4] = {3, 2, 4, 2};
int dp[5][6];

//
//         o
//       ↙ ↘
//      o     o
//    ↙ ↘ ↙ ↘
//  ...  ...  ...
// 不选的情况下分支出一条路径, 选的情况下分支出一条路径
// 本质两条路径 2^n, 在参数相同的情况下, 分支出相同的答案, 第二次计算只会浪费计算时间
// 所以我们只第一次计算出的结果, 朴素 dfs 在参数少的情况下可以改记忆化搜索
int dfs(int u, int rest)
{
    int ans = 0;
    if (u == n) ans = 0;
    else if (rest < w[u]) ans = dfs(u + 1, rest);       // else if 是为了连接下面的 else
    else ans = max(dfs(u + 1, rest), dfs(u + 1, rest - w[u]) + v[u]);
    return ans;
}

// 注意该写法的下标是从 0 开始的
void test_dp()
{
    for (int i = 0; i < n; ++ i)
        for (int j = 0;  j <= m; ++ j)
        {
            // 第 i+1 号物品不选择
            dp[i + 1][j] = dp[i][j];        
            // 第 i+1 号物品选择 
            if (j >= w[i]) 
            {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j - w[i]] + v[i]);
            }
        }
    printf("%d", dp[n][m]);
}

int main()
{
    // printf("%d", dfs(0, m));
    test_dp();
    return 0;
}
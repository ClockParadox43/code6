
`时间复杂度为: O(N*M)`
```c++ 
思路: 由于是字典序我们要从前往后来判断每个物品是否选择物品
状态表示:dp[i][j]表示从第i件物品到最后一件物品, 体积不超过j所能装的最大价值
        way[i][j]表示从第i件物品到最后一件物品,体积不超j的最优方案中所选的第一个物品编号
阶段划分: 物品种数
转移方程: dp[i][j] = max(dp[i+1][j-v[i]]+w[i],dp[i+1][j]) 第一种是需要在j >= v[i]的时候成立
         由于我们要尽可能的选择第i件物品，那么当dp[i + 1][j - v[i]] + w[i] >= dp[i][j]时我们就要将way[i][j] = i;
边界:    dp[N + 1][0] = 0;
```
```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e3 + 10;

int n, m;
int dp[N][N];
int v[N], w[N];
int way[N][N];

void print(int x, int y)
{
    if (x == n + 1) return; 
    int k = way[x][y];  
    // 判断是否选择了第 x 件物品
    if (k) cout << k << ' '; 
    // 在递归函数的上面为由根节点到叶子节点进行操作
    print(x + 1, y - v[k]);
    // 在递归函数的下面进行操作, 为叶子节点遍历完了, 回溯由子节点到根节点进行操作
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) cin >> v[i] >> w[i];
    // 注意计算当前阶段的状态需要之前的转态已经计算过了
    for (int i = n; i >= 1; -- i)
        for (int j = 1; j <= m; ++ j)
        {
            dp[i][j] = dp[i + 1][j];
            if (j >= v[i])
                if (dp[i][j] <= dp[i + 1][j - v[i]] + w[i])  
                {
                    // 记录转移时候的路径
                    // 注意我们要尽可能的选择第i件物品，因为我们从前往后来判断是否选择物品
                    dp[i][j] = dp[i + 1][j - v[i]] + w[i];
                    way[i][j] = i;
                }
        }

    print(1, m);
    return 0;
}
```
#include <iostream>

using namespace std;
const int MAXN = 1e3 + 5;

int n, m;
int v[MAXN], w[MAXN];
int dp[2][MAXN];

int main()
{
    scanf("%d%d", &n, &m);
    
    for (int i = 0; i < n; ++ i)
        scanf("%d%d", &w[i], &v[i]);
        
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= m; ++j)
        {
            // 当前重量不够当前物品的重量, 
            // 那就选在前 i-1(i 从 1 开始话是 i-1, 从 0 开始的话是 i) 个中选最优解
            if (j < w[i]) 
                dp[(i + 1) & 1][j] = dp[i & 1][j];  
            else 
                dp[(i + 1) & 1][j] = max(dp[i & 1][j], dp[(i + 1) & 1][j - w[i]] + v[i]);
            // 完全背包依赖的是当前行的值, 会在之前的选择上叠加物品个数
            // dp[(i + 1) & 1][j - w[i]]: 所以针对不同重量, 在当前行物品要选择 k 个   
            // dp[i & 1][j]: 和上一行不同重量下的各个最优解进行比较
        }

    printf("%d", dp[n & 1][m]);
        
    return 0;    
}
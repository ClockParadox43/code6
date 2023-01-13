#include <iostream>

using namespace std;
const int MAXN = 1e3 + 5;

int n, m;
int v[MAXN], w[MAXN];
int dp[2][MAXN];

int main()
{
    scanf("%d%d", &n, &m);
    
    for (int i = 1; i <= n; ++ i)
        scanf("%d%d", &w[i], &v[i]);
        
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
        {
            if (j < w[i]) 
                dp[(i + 1) & 1][j] = dp[i & 1][j];      // 当前行依赖另一行, 没有选择新物品的情况
            else 
                dp[(i + 1) & 1][j] = max(dp[i & 1][j], dp[i & 1][j - w[i]] + v[i]);    
                // dp[i & 1][j]: 上一次选择的最优解
                // dp[i & 1][j - w[i]] + v[i]:在上一次的最优解情况下要当前物品
                // ps: dp[i & 1][j] 不能写成 dp[i & 1][j - w[i]], dp[i & 1][j - w[i]] 是当前层, 
                //     如果用当前层去更新那么更新的就是下一件物品(也就是下一层的)是否选择的值了
        }
    
    // 为什么是 (n + 1) & 1
    // 从偶数位 (1+1)&1 开始推的, 代入一下, 假设 n=4, 偶奇偶奇
    // 推 4 轮后答案在奇数位, 那么就是 (4+1)&1 确定在奇数位
    printf("%d", dp[(n + 1) & 1][m]);
        
    return 0;    
}
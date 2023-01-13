
// 集合角度思考
//                      ↗ 集合: 所有从 [1,1] 走到 [i,j] 的所有可能的路线的最大值 
//             状态表示 ↘ 属性: max
//          ↗ 
// 动态规划
//          ↘   
//             状态计算(状态的划分)
//                _________________
//               |最后一步|最后一步|
//               |从上下来|从左过来|
//              
#include <iostream>

using namespace std;
const int MAXN = 105;

int Q, n, m;
int w[MAXN][MAXN];
int dp[MAXN][MAXN];

int main()
{
    scanf("%d", &Q);
    while (Q -- )
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++ i)   
            for (int j = 1; j <= m; ++ j)
                scanf("%d", &w[i][j]);
        
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= m; ++ j)
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + w[i][j];
        
        printf("%d\n", dp[n][m]);
    }
    
    return 0;
}
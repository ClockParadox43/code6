// 分析: 只能经过 2n-1 个点, 只能从上方或者左边走过来, 属于数字三角模型
// 
// 状态表示: 集合f[i,j]:从起点走到 (i,j) 的最少代价
//           属性: min
// 状态计算: f[i-1][j], f[i][j-1]
//
// 错误原因: 边界没有调好
#include <iostream>

#define INF 0x3f3f3f3f
#define MAXN 104
using namespace std;

int n;
int w[MAXN][MAXN];
int f[MAXN][MAXN];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            scanf("%d", &w[i][j]);
    
    for (int i = 1; i <= n; ++ i)       
        for (int j = 1; j <= n; ++ j)
            if (i == 1 && j == 1) f[i][j] = w[i][j];    
            else        // 这里要添加 else, 防止 (1,1) 被覆盖掉, 这里被坑了
            {
                f[i][j] = INF;
                if (i > 1) f[i][j] = min(f[i][j], f[i - 1][j] + w[i][j]);
                if (j > 1) f[i][j] = min(f[i][j], f[i][j - 1] + w[i][j]);
            }
        
    
    printf("%d", f[n][n]);
    return 0;
}

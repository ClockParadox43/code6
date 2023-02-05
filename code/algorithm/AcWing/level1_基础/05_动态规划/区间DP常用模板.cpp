#include <iostream>
#include <cstring>

using namespace std;

/*
    所有区间 dp 问题枚举时, 第一维通常是枚举区间长度, 
    并且一般 len = 1 时用来初始化, 枚举从 len = 2 开始, 第二维枚举起点 i
    (右端点 j 自动获得, j = i + len - 1) 

    for (int len = 1; len <= n; ++ len )
        for (int i = 1; i + len - 1 <= n; ++ i )
        {
            int j = i + len - 1;        // 终点
            if (len == 1)
            {
                dp[i][j] = 初始值;
                continue;
            } 

            // 枚举分割点，构造状态转移方程
            for (int k = 1; k < j; ++ k )
                dp[i][j] = min(dp[i][j], dp[i][j] + dp[k + 1][j] + w[i][j]);
        }
*/ 

// 模板题:合并石子代码
const int N = 310;

int a[N], s[N];
int f[N][N];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++ i )
    {
        scanf("%d", &a[i]);
        s[i] += s[i - 1] + a[i];
    }

    memset(f, 0x3f, sizeof f);

    // 区间 DP 枚举套路:针对每个长度枚举区间(左右端点), 针对每个区间枚举划分点, 求最小的合并代价
    // 合并代价:之前的合并代价 + 当前的合并代价
    // f[i,j] 集合就是, 某个长度内, 从 l 到 r 的最小的合并代价(l/r 被长度包括)
    for (int len = 1; len <= n; ++ len )            // len 表示 f[i,j] 的元素个数
        for (int i = 1; i + len - 1 <= n; ++ i )    // 起点
        {
            int j = i + len - 1;                    // 右端点
            
            // 区间中只有一个数, 合并代价为 0
            if (len == 1)
            {
                f[i][j] = 0;    // 边界初始化
                continue;
            }

            // 枚举分割点
            // 必须满足k + 1 <= j, 右边必须还剩下数
            // 之前的合并结果 + 当前合并总代价
            for (int k = i; k <= j - 1; ++ k )
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + s[j] - s[i - 1]);
        }

    printf("%d", f[1][n]);

    return 0; 
}
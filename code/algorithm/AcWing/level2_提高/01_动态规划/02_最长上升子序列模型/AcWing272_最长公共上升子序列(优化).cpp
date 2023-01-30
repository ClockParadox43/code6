// 优化就是对代码做等价变形
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 3010;

int n;
int a[N], b[N];
int f[N][N];
int g[N][N];    // 代替 maxv, 表示满足 a[i] > b[j] 的所有 f[i-1,j]+1 的最大值 

void pre()
{
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
        {
            f[i][j] = f[i - 1][j];              
            
            if (a[i] == b[j])                   
            {
                f[i][j] = max(f[i][j], 1);      
                
                // 内层循环的含义是从 k(1 <= k <= j-1) 中, 找到 f[i-1][k] 的最大值
                // 因此我们发现, 该条件和第二层循环的 j 是没有关系的, 所以该条件可以被拿到循环外面去
                // 也就是, 满足某一个和 j 没有关系的条件的情况下他某个前缀的最大值
                // 满足某个前缀的最大值可以用变量来存储
                for (int k = 1; k < j; ++ k)
                    if (b[j] > b[k])  // 因为在执行这段执行时, a[i] = b[j], 所以 b[j]可以替换成 a[i]
                        f[i][j] = max(f[i][j], f[i - 1][k] + 1); 
            }                                                    
        }
}

void test()
{
    for (int i = 1; i <= n; i ++ )
    {
        g[i][0] = 1;        
        for (int j = 1; j <= n; j ++ )
        {
            f[i][j] = f[i - 1][j];
            // 循环求的就是, a[i] > b[j] 的所有 f[i-1,j]+1 的最大值 
            if (a[i] == b[j]) f[i][j] = max(f[i][j], g[i][j - 1]); 
            g[i][j] = g[i][j - 1];
            if (a[i] > b[j]) g[i][j] = max(g[i][j], f[i - 1][j] + 1);   
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &b[i]);

    for (int i = 1; i <= n; i ++ )
    {
        int maxv = 1;   // 表示以 a[i] 结尾的 f[i,j] 集合的最大值
        for (int j = 1; j <= n; j ++ )
        {
            f[i][j] = f[i - 1][j];
            // a[i] 和 b[j] 都是序列的最后一个
            if (a[i] == b[j]) f[i][j] = max(f[i][j], maxv); 
            // f[i - 1][j]: 表示所有不包含 a[i] 的公共子序列, 都不包含 a[i]了, 所以不需要判断 a[i] 和 b[j] 是否相等
            if (a[i] > b[j]) maxv = max(maxv, f[i - 1][j] + 1);   
        }
    }

    int res = 0;
    for (int i = 1; i <= n; i ++ ) res = max(res, f[n][i]);
    printf("%d\n", res);

    return 0;
}
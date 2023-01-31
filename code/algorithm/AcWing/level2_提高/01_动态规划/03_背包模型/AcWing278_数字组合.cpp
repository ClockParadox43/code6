// 1 1 2 2
//
// p1: 1 1 2  -> 固定第一个 1, 选第 1 个 2
// p2: 1 1 2  -> 固定第一个 1, 选第 2 个 2
// p3: 2 2
// 
// 选和不选属于 01背包问题
//
// M 看成背包容量
// 每个数看做物品, Ai 看成是体积
// 目标: 求出总体积恰好是 M 的方案数
//    
//                   集合: 所有只从前 i 个物品中选, 且总体积恰好是 j 
//                  /      且总体积不超过 k 的所有方案集合 
//    状态表示f[i,j]
//   /              \ 
// DP                属性: M
//   \
//    状态计算 f[i,j]

// 不包括i的所有选法:f[i-1,j]
// 包括i的所有选法:f[i-1, j-v] -> 想要包括 i 且不超过为 i 腾出位置   
// 两边的数量之和就是f[i,j] 的总方案数 f[i,j] = f[i-1,j]+f[i-1,j-v]
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110, M = 10010;

int n, m;
int v[N];
int f[N][M];        // 选或不选某个数字

int main()
{
    scanf("%d%d", &n, &m);
    f[0][0] = 1;
    for (int i = 1; i <= n; ++ i ) scanf("%d", &v[i]);
    
    for (int i = 1; i <= n; ++ i )  
        for (int j = 0; j <= m; ++ j )      // 枚举每个数恰好是 j 时还需要多少, 直到 m 
        {
            f[i][j] = f[i - 1][j];
            if (j >= v[i])                   
                f[i][j] += f[i - 1][j - v[i]];
        }    
        
    cout << f[n][m] << endl;
}
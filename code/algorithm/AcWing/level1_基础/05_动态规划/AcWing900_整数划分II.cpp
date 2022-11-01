// 思路2:
// 状态表示f[i,j]: 所有总和是 i, 并且恰好表示成 j 的方案数
// 属性: 数量
// 集合划分: 
//  1) 表示 j 个数的和中最小值是 1
//      - 因为最小值是 1, 每个方案都存在一个 1, 每个方案的 1 去掉
//        那么该方案总和就剩下 i-1, 表示成 j-1 个数的和的这样的方案        
//      转移方程: f[i-1,j-1]   
//  2) 表示 j 个数中最小值大于 1
//      - 总和是 i, 表示成 j 个数的和, 并且每个数个数大于 1, 那么每个数个数 - 1, 那么总和就是减 j
//        因为最小值大于 1, 所以就算减 1 也还剩下 j 个正整数
//      转移方程: f[i-j, j]
// 最后就可以得到 f[i,j] 的状态转移方程 f[i,j] = f[i-1,j-1] + f[i-j,j]

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010, mod = 1e9 + 7;

int n;
int f[N][N];

int main()
{
    scanf("%d", &n);

    f[0][0] = 1;
    for (int i = 1; i <= n; ++ i )  
        for (int j = 1; j <= i; ++ j )
            f[i][j] = (f[i - 1][j - 1] + f[i - j][j]) % mod;
    
    int res = 0;
    for (int i = 1; i <= n; ++ i ) res = (res + f[n][i]) % mod;

    printf("%d", res);
    return 0;
}
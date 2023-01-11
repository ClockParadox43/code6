// 状态表示: 1) 集合f[i][j], 每 i 个物品可以重复选择, 在不超过 s[i] 个的情况下, 在不同状态的 j 中的最大值
//              j 从小到大枚举, 不管是添加还是覆盖都会选择最大值
// 
//           2) 属性: Max
//
// 状态计算: 不选择 f[i - 1][j]
//             选择 f[i - 1][j - k * v[i]] + w[i]
// 

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;

int n, m;
int v[N], w[N], s[N];
int f[N][N];

int main()
{
    scanf("%d%d", &n, &m);
    
    for (int i = 1; i <= n; ++ i ) scanf("%d%d%d", &v[i], &w[i], &s[i]);
    
    for (int i = 1; i <= n; ++ i )
        for (int j = 0; j <= m; ++ j )
            for (int k = 0; k * v[i] <= j && k <= s[i]; ++ k ) 
                f[i][j] = max(f[i][j], f[i - 1][j - v[i] * k] + w[i] * k);
        
   
    printf("%d", f[n][m]);         
    return 0;
}
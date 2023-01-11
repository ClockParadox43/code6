// 状态表示 f[i,j]: 在不超过体积 j 的情况下求出最大价值是多少
//            属性: Max
// 
// 状态计算: 当前物品 i 选择, 当前物品 i 不选择
//           如果当前物品 i 不选择, 那么还是拿当前 j 位置上的最好答案
//           f[i-1][j]
//           如果当前物品 i 选择, 那么为当前物品腾出 v[i] 的体积, 
//           获得体积 j 减去 v[i] 时候的最好价值, 累加上当前价值
//           f[i-v[i], j] + w[i]


#include <iostream>

using namespace std;

const int N = 1010;

int n;
int v[N], w[N];
int f[N][N];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    
    for (int i = 1; i <= n; ++ i ) scanf("%d%d", &v[i], &w[i]);
    
    for (int i = 1; i <= n; ++ i )
        for (int j = 0; j <= m; ++ j )      // j 和 v[i] 的属性都是重量, 所以 j 减去 v[i](为放重量为 v[i] 的物品腾出空间)
        {
            f[i][j] = f[i - 1][j];
            if (j >= v[i]) f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
        }
    
    cout << f[n][m] << endl;
    
    return 0;
}
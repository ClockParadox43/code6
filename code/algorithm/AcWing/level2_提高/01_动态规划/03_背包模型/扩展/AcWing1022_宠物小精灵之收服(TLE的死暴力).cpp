// 选择: 减少w, 减少wl, 增加 v
// 不选择: 不减少w, wl, 不增加v
//
// 状态表示 f[i,j,h]: 选择前 i 个物品, 在血量和球的数量足够的情况下的最好代价
//              属性: Max
// 状态计算: 选择 f[i - 1][j - wl[i]][h - w[i]] + 1
//           不选择 f[i - 1][j][h]
#include <iostream>

#define MAXN 1003 
#define MAXM 501
#define MAXK 103
using namespace std;

int n, m, k;    // 球数量, 体力, 精灵数量
int w[MAXN], wl[MAXN]; // 每个物品对应的球的数量和血量
int f[MAXK][MAXM][MAXN];

int main()
{
    cin >> k >> m >> n;
    
    for (int i = 1; i <= n; ++ i)
        cin >> w[i] >> wl[i];   // 物品所对应的双费
    
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j <= m; ++ j)
            for (int h = 0; h <= k; ++ h)
            {
                f[i][j][h] = f[i - 1][j][h];
                if (j >= wl[i] && h >= w[i])
                    f[i][j][h] = max(f[i][j][h], f[i - 1][j - wl[i]][h - w[i]] + 1);
            }
    
    
    // 找到满足最大价值的所有状态里，血量那维度 消耗最少的
    int rest_hp = m, res = 0;
    for (int i = 0; i <= m; ++ i)
        if (f[n][i][k] > res)           // 如果最大价值 > res
        {
            res = f[n][i][k];           // 更新最大价值
            rest_hp = m - i;            // 血量减去哪一位度用掉的血量
        }
        
    cout << res << ' ' << rest_hp << endl;
    return 0;
}
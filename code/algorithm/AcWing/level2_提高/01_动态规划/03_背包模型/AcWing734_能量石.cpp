// 因为对于第i和i+1块能量石,我们可以利用排序不等式证明出先吃第i块石头的能量大于后吃第i块石头的能量
// 将Ei+1记作Ej有 Ei+Ej-Si*Lj > Ej+Ei-Sj*Li
// 减去的"所消耗的能量"越少就意味着"得到的能量"越多, 有 Si*Lj < Sj*Li = Si/Li < Sj/Lj
// ps:当吃到第j块石头总能量: 即减去吃Ei消耗的时间乘i+1块石头每秒消耗的能量
// 
// 因为一定存在一组最优解, 是按特定顺序吃的, 所以我们只需要考虑按特定顺序排序的所有方案即可
// 在这些方案里找到的最大值(因为是最优解), 一定就是最大值, 所以之后就可以用01背包问题解决就行了
//
// 状态表示f[i,j]:考虑前i个魔法石, 且吃掉最后一个魔法石后, 所用总时间恰好为j的方案
//             ps:这里求的是恰好, 并不是时间越多越好, 因为时间过去的越多代表消耗的能量也就越多
//           属性:max(吃能量石获得的最大能量是多少代表最大价值)
// 状态计算f[i,j]:
//      - 吃掉第i个魔法石: f[i-1,j-si]+ei-(j-si)*li  
//            ps:   
//             - j-si:为第i块能量石所消耗的时间腾出空间
//             - 加上第i块石头的初始能量减去消耗的能量:+ei-(j-si)*li
//      - 不吃第i个魔法石: f[i-1,j]
//
// 时间复杂度: O(N*∑si)
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010;

struct Stone
{
    int s, e, l;
    bool operator<(const Stone &W) const { return s * W.l < l * W.s; }
}stones[N];
int n;
int f[N][N];

int main()
{
    int T; cin >> T;
    for (int C = 1; C <= T; ++ C)
    {
        int m = 0; cin >> n;
        for (int i = 1; i <= n; ++ i)
        {
            int s, e, l; cin >> s >> e >> l;
            stones[i] = {s, e, l};
            m += s;
        }
    
        sort(stones + 1, stones + 1 + n);
        for (int i = 1; i <= n; ++ i)
            for (int j = 0; j <= m; ++ j)
            {
                f[i][j] = f[i - 1][j];
                if (j >= stones[i].s)
                {
                    int s = stones[i].s, e = stones[i].e, l = stones[i].l;
                    f[i][j] = max(f[i][j], f[i - 1][j - s] + max(0, e - (j - s) * l));
                }
            }
        
        // 枚举所有体积
        int res = 0;
        for (int i = 0; i <= m; ++ i)
            res = max(res, f[n][i]);
        cout << "Case #" << C << ": " << res << endl;
    }
    return 0;
}
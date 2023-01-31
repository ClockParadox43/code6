
// 状态表示:f[i,j,k]:前i个物品中,体积不超过当掐容量, 重量小于当前重量的最大价值
// 属性:max
// 装他计算: 
//      选择: f[i-1][j-v][k-vl] + w
//      不选择:f[i-1][j][k] 
#include <iostream>

#define MAXN 1001
using namespace std;

int n, m, s;
int f[MAXN][MAXN];

int main()
{
    cin >> n >> m >> s;         // 个数, 体积, 重量
    for (int i = 0; i < n; ++ i)
    {
        int v, vl, w; cin >> v >> vl >> w;
        for (int j = m; j >= v; -- j)
            for (int k = s; k >= vl; -- k)
                f[j][k] = max(f[j][k], f[j - v][k - vl] + w);
    }
    cout << f[m][s] << endl;
    return 0;
}

// 状态表示f[i,j]:选择前i种物品, 在不超过价格和最大数量的情况下,使价值尽可能大
// 集合:max
// 状态计算: 不选择第i件物品f[i-1,j]
//           选择第i件物品f[i-1,j-kv]+kw
#include <iostream>

using namespace std;

const int MAXN = 510, MAXM = 6001;

int n, m;
int f[MAXN][MAXM];

int main()
{
    cin >> n >> m;
    // cout << n << m << endl;
    for (int i = 1; i <= n; ++ i)
    {
        int v, w, s; cin >> v >> w >> s;
        for (int j = 0; j <= m; ++ j)
        {
            f[i][j] = f[i - 1][j];
            for (int k = 0; k <= s && k * v <= j; ++ k)
                f[i][j] = max(f[i][j], f[i - 1][j - k * v] + k * w);
        }
    }
    
    cout << f[n][m] << endl;
    return 0;
}
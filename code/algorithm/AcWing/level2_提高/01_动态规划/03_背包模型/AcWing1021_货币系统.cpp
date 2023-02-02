// 状态表示f[i,j]:前i件物品组成恰好为m的方案数
//           属性:cnt
//       状态计算:f[i,j] += f[i-1,j-w]

#include <iostream>

#define N 20
#define M 3005
using namespace std;
typedef long long ll;

int n, m;
ll f[N][M];

void op()
{
    cin >> n >> m;
    f[0] = 1;
    for (int i = 1; i <= n; ++ i)
    {
        int v; cin >> v;
        for (int j = v; j <= m; ++ j) f[j] += f[j - v];
    }
    cout << f[m] << endl;
}

int main()
{
    cin >> n >> m;
    f[0][0] = 1;
    for (int i = 1; i <= n; ++ i)
    {
        int v; cin >> v;
        for (int j = 0; j <= m; ++ j)
            for (int k = 0; k * v <= j; ++ k)       // 枚举选择i能组成f[i,j]的方案
                f[i][j] += f[i - 1][j - k * v];
    }
    cout << f[n][m] << endl;
    return 0;
}
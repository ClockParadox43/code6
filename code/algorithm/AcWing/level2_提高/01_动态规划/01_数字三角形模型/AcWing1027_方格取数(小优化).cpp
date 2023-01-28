#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 15, MAXM = MAXN << 1;

int n, x, y, c;
int f[MAXM][MAXN][MAXN], w[MAXN][MAXN];

int main()
{
    cin >> n;
    while (cin >> x >> y >> c, x || y || c) w[x][y] = c;

    // 这一步本质是横坐标不断增加对情况下, 不断更新在当前横坐标内可能走到每个点的最大值
    // 也就是, 随着 k 每一次的增加, 也对应着纵坐标到改变(k=x1+y1=x2+y2)
    // 随着横纵坐标的不同, 枚举每一次更新
    for (int k = 2; k <= n << 1; ++ k)
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= n; ++ j)
            {
                // 但是最开始 k 很小, 而 i, j 越来越大, 所以 _i, _j 会小于 0
                int _i = k - i, _j = k - j;
                if (_i <= 0 || _j <= 0) break;
                if (_i > n || _j > n) continue;     // 不能 break, 继续 ++ j 还能拉回来, j 越大 _j 就越小, 然后就不会超过了
                if (_i >= 1 && _i <= n && _i >= 1 && _j <= n)
                {
                    int t = w[i][_i];
                    if (i != j) t += w[j][_j];
                    int &v = f[k][i][j];
                    v = max(v, f[k - 1][i - 1][j - 1] + t);
                    v = max(v, f[k - 1][i][j - 1] + t);
                    v = max(v, f[k - 1][i - 1][j] + t);
                    v = max(v, f[k - 1][i][j] + t);
                } 
            }
    
    cout << f[n << 1][n][n] << endl;
    return 0;
}


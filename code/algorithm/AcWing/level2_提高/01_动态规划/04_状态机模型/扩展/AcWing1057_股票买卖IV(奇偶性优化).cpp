#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 10, M = 110;

int n, k;
int w[N];
int f[2][M][2];

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; ++ i) cin >> w[i];

    memset(f, -0x3f, sizeof f);
    f[0][0][0] = 0; //初始状态f[0][0][0]

    for (int i = 1; i <= n; ++ i)
    {
        for (int j = 0; j <= k; ++ j)
        {
            f[i & 1][j][0] = f[(i - 1) & 1][j][0];
            // 边界
            if (j) f[i & 1][j][0] = max(f[i & 1][j][0], f[(i - 1) & 1][j - 1][1] + w[i]);
            f[i & 1][j][1] = max(f[(i - 1) & 1][j][1], f[(i - 1) & 1][j][0] - w[i]);
        }
    }

    int res = 0;
    for (int j = 0; j <= k; ++ j) res = max(res, f[n & 1][j][0]); //目标状态f[n][j][0]

    cout << res << endl;

    return 0;
}

作者：一只野生彩色铅笔
链接：https://www.acwing.com/solution/content/55037/
来源：AcWing
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
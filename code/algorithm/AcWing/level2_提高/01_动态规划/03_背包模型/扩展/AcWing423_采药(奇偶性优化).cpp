// 观察到朴素版的代码里, 每个阶段 i 的状态转移, 只依靠 i-1 层的状态
// 因此我们可以通过 滚动数组 或者 代码等价变形 来优化掉后续不再使用的空间
#include <iostream>

#define MAXN 1003
using namespace std;

int n, m;
int w[MAXN], v[MAXN];
int f[2][MAXN];
int main()
{
    cin >> m >> n;
    for (int i = 1; i <= n; ++ i) cin >> w[i] >> v[i];
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j <= m; ++ j)
        {
            f[i & 1][j] = f[i - 1 & 1][j];      // 如果是奇数就依赖偶数位, 偶数就依赖奇数位
            if (j >= w[i]) f[i & 1][j] = max(f[i & 1][j], f[i - 1 & 1][j - w[i]] + v[i]);
        }
    cout << f[n & 1][m] << endl;
    return 0;
}


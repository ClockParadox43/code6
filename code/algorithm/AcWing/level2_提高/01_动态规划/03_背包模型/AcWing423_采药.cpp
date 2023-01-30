// 背包裸题, 直接优化
// 状态表示: 在前 i 个物品中，且使用体积不超过 j 的最大值
#include <iostream>

#define MAXN 1003
using namespace std;

int n, m, w, v;
int f[MAXN];

int main()
{
    cin >> m >> n;
    for (int i = 0; i < n; ++ i)
    {
        cin >> w >> v;
        for (int j = m; j >= w; -- j)
            f[j] = max(f[j], f[j - w] + v);
    }
    cout << f[m] << endl;
    return 0;
}

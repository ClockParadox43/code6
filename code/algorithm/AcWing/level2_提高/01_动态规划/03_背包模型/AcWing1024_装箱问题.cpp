// 背包裸题, 直接优化
// 状态表示f[i,j]:从前 i 个物品中选选择体积小于 j 的重量
#include <iostream>

#define MAXN 20001
using namespace std;

int n, m, w;
int f[MAXN];

int main()
{
    cin >> m >> n;
    for (int i = 0; i < n; ++ i)
    {
        cin >> w;
        for (int j = m; j >= w; -- j)
            f[j] = max(f[j], f[j - w] + w);
    }
    cout << m - f[m] << endl;
    return 0;
}
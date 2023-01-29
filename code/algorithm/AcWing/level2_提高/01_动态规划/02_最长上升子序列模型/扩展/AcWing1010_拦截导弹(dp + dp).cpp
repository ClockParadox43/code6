#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1004;
int n, ans, ansl;
int w[MAXN];
int f[MAXN], g[MAXN];

// 第一问:显然每套导弹拦截系统拦截导弹高度为不升子序列, 求最长的就好了
// 第二问:求导弹拦截系统的个数可以转化为求最长上升子序列长度
int main()
{
    while (cin >> w[n]) n ++ ;
    for (int i = 0; i < n; ++ i)
    {
        f[i] = g[i] = 1;
        for (int j = 0; j < i; ++ j)
        {
            if (w[i] <= w[j]) f[i] = max(f[i], f[j] + 1);
            else g[i] = max(g[i], g[j] + 1);
        }
        ans = max(ans, f[i]), ansl = max(ansl, g[i]);
    }
    cout << ans << endl << ansl << endl;
    return 0;
}
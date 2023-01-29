#include <iostream>

#define MAXN 1003
using namespace std;

int n, ans, ansl;
int w[MAXN];
int f[MAXN], g[MAXN];

int main()
{
    while (cin >> w[n]) n ++ ;

    for (int i = 0; i < n; ++ i)
    {
        f[i] = 1;
        for (int j = 0; j < i; ++ j)
            if (w[i] <= w[j]) f[i] = max(f[i], f[j] + 1); 
        ans = max(f[i], ans);
    }

    cout << ans << endl;

    // 为什么可以这样做? 就是证明了递减序列组g[i] 由 递减序列结尾的那个数, 组成 
    // 证明了 g[i] 序列是单调递增的, 所以我们可以在序列上二分
    // 找小于当前位置的最大的数
    for (int i = 0; i < n; ++ i)
    {
        int l = 0, r = ansl;
        while (l < r)
        {
            int m = l + r >> 1;
            if (g[m] >= w[i]) r = m;
            else l = m + 1; 
        }  
        if (w[i] > g[l]) l ++ ; // 没有找到小于 "当前数" 的数即, "当前数" 大于 "所有递减序列" 中的数
        ansl = max(ansl, l);    // 找到会更新该位置, 没有找到一定会二分到最右边, 所以对于之前答案求一个最值 
        g[l] = w[i];            // 开启一个新的序列
    }

    cout << ansl << endl;
    return 0;
}
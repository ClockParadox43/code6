// 简单说一下求上升子序列和求几组上升子序列的区间
// 已知: l 找到的永远是符合条件的数
// 求上升/下降子序列:
//      - 找到符合条件的数然后将该数插入在符合条件数的后面, 因为是插入在符合条件的数的后面, 所以随时需要 l+1
// 求几组上升/下降序列:
//      - 找到符合条件的数, 将该数覆盖, 当需要出现新组的时候才可以开辟, 所以需要判断一下 l 才能加 1

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
    // 下降子序列也是枚举每个结尾让数尽可能的大(贪心), 找大于 x 的最小的数
    for (int i = 0; i < n; ++ i)
    {
        int l = 0, r = ansl;
        while (l < r)
        {
            int m = l + r >> 1;
            if (g[m] >= w[i]) r = m;
            else l = m + 1; 
        }  
        if (w[i] > g[l]) l ++ ; // 情况1: 没有找到大于 x 的数即, 也就是出现了递增序列, 需要另外开新组
        ansl = max(ansl, l);    // 找到会更新该位置, 没有找到一定会二分到最右边, 所以对于之前答案求一个最值 
        g[l] = w[i];            // 情况2: l 找到的是大于 x 的最小的数, 贪更好的值 
    }

    cout << ansl << endl;
    return 0;
}
// 我们要求一个先上升后下降的序列, 那么转折点是关键
// 可以发现, 转折点前的序列要求上升, 转折点后的序列(如果反着看)也要求上升
// 那么所求 = 总人数 - 上升序列人数
// 所以直接枚举转折点，正反跑两遍 LIS 不就完事了吗

// 思路: 1. 以长度为单位找最小值, f[] 中的就是以当前长度为单位能排升序的人,
//          用 point 记录人数.
//       2. 总人数就是 i, 用 i-point 就是所求 
// 
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 103;

int n, ans = MAXN;
int w[MAXN], f[MAXN], l[MAXN], r[MAXN];
// l[i] 表示以 i 为转折点 0~i 符合合唱队形 所删的最少人数
// r 类似

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) scanf("%d", &w[i]);
    
    f[1] = w[1];
    int point = 1;

    for (int i = 2; i <= n; ++ i)
    {
        // 如果当前值(w[i])大于, 升序数组(f[i])中的值, 就插在后面 (能排升序就排升序)
        if (w[i] > f[point]) f[ ++ point] = w[i];         
        else 
        {   
            // w[i] < f[point], 找到大于 w[i] 的最小的数, 替换掉
            int x = lower_bound(f + 1, f + point + 1, w[i]) - f;
            f[x] = w[i];
        }
        l[i] = i - point;
        // i 是总人数, point 是升序人数, 剩下的 = 总人数 - 上升序列人数
    }

    memset(f, 0, sizeof f);
    f[1] = w[n];
    point = 1;
    for (int i = n - 1; i >= 1; -- i)
    {
        if (w[i] > f[point]) f[ ++ point] = w[i];
        else 
        {
            int x = lower_bound(f + 1, f + point + 1, w[i]) - f;
            f[x] = w[i]; 
        }
        r[i] = n - i + 1 - point;
    }

    for (int i = 1; i <= n; ++ i) ans = min(ans, l[i] + r[i]);
    printf("%d", ans);
    
    return 0;
}
// 公路上有n个加油站, 汽车是否能"顺时针/逆时针"转完一圈
// 1) 找起点, 破环为链, 2n
// 2) 如何快速判断是否能转完一圈
//    判断当前加油站否能到达下一站: 当前加油站油量 - 到下一站的距离 
//    我们可以将差值存储在数轴上
// 3) 到转弯一圈是安全的等价于前n个数的前缀和的值>=0
//    转化成:
//    长度为n的区间内, 所有前缀和的最小值是否>=0

#include <iostream>

using namespace std;

const int N = 2e6 + 10; // 破环成链, 开2倍空间
typedef long long ll;

int n;
int o[N], d[N];
ll s[N];  // 顺时针时表示p[i]-d[i]的前缀和, 逆时针时表示p[i]-d[i-1]的后缀和
int q[N]; // 单调队列维护长度为n的区间中s[i]的最小值
bool st[N];
// o[i]表示到i地点所需要的油,
// d[i]表示i到i+1消耗的油,
// st[i]等于1时表示能环球旅行,0时不能

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++ i) 
        cin >> o[i] >> d[i];

    // 顺时针 -> oi-di
    for (int i = 1; i <= n; ++ i)
        s[i] = s[i + n] = o[i] - d[i];
    for (int i = 1; i <= n * 2; ++ i) 
        s[i] += s[i - 1];
    
    int hh = 0, tt = -1;
    // 从大到小枚举i, 然后考虑区间[i,i+n-1]中的最小值是否>=s[i-1]
    for (int i = n * 2; i; -- i)
    {
        if (hh <= tt && q[hh] > i + n - 1) ++ hh;       // 窗口的范围为n 窗口:[i, i+n-1]
        while (hh <= tt && s[q[tt]] >= s[i]) -- tt;     // 保持单调递增, q中大于s[i]的都出队
        q[ ++ tt] = i;         // s[i]入队

        // 此时队头元素就是区间min, 表示以i起起始顺时针走有解
        if (i <= n && s[q[hh]] >= s[i - 1]) st[i] = true;
    }


    // 逆时针 -> oi-di-1(逆时针要减去前面的di, 忘了画图)

}
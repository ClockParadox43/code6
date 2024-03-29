// 公路上有n个加油站, 汽车是否能"顺时针/逆时针"转完一圈
// 
// 剩余油量 = 当前油量 - 当前点到下一个加油站距离
// 所以我们可以将这个差值存在数组种, 生成前缀和 (从含义出发, 前缀和中值就代表到每个点真正剩余的油量) 
// 所以从当前点走到下一个点是安全的等价于, 这个区间内的前缀和都是 >= 0 
//
// 1) 从某个点i出发, 顺时针走一圈, 过程中油量始终>=0, 等价于在 [i, i+n-1] 中, 对任意的j
//    i <= j <= i+n-1, 均有 s[j] - s[i-1] >= 0, 即i固定, 找到s[j]的最小的值, 即从
//    [i,i+n-1] 中找到滑动窗口的最小值
//    j: 右端点剩余的油量, i-1: 最开始剩余的油量 
//         
//
//  ps:因为顺时针做的时候, 因为是枚举起点找到每个点后面一段区间的最值, 因此需要从后往前扫
//     这样才能在求当前点的信息时, 将后面的信息保存下来
//     s[i] - q[hh], hh:是这段窗口内最小的点(也就是后面的值) 

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
    for (int i = 1; i <= n; ++ i) cin >> o[i] >> d[i];

    // 顺时针求 p[i]-d[i]的前缀和
    for (int i = 1; i <= n; ++ i) s[i] = s[i + n] = o[i] - d[i];
    for (int i = 1; i <= n * 2; ++ i) s[i] += s[i - 1];

    // 从大到小枚举i, 然后考虑区间[i, i+n-1]中的最小值是否>=s[i-1]
    int hh = 0, tt = -1;
    for (int i = n * 2; i; -- i)
    {
        if (hh <= tt && q[hh] > i + n - 1) ++ hh;   // 判断是否划出[i,i+n-1]
        while (hh <= tt && s[q[tt]] >= s[i]) tt -- ;
        q[ ++ tt] = i;
        // 此时队头元素就是区间的min
        // 因为我们要记录的是后面区间的最小值, 我们想要这个最小值 - i-1 >= 0(后面的最小之减起点), 所以从后往前枚举
        // 如果从前往后枚举, 只能用i减hh, 这是判断不出来的
        if (i <= n && s[q[hh]] >= s[i - 1]) st[i] = true; // 表示以i为起点顺时针有解
    }

    // 逆时针求 o[i]-d[i-1]的后缀和
    d[0] = d[n];        
    for (int i = n; i; -- i) s[i] = s[i + n] = o[i] - d[i - 1];
    for (int i = n * 2; i; -- i) s[i] += s[i + 1];
    // 从小到大枚举i, 然后考虑区间[i-n+1,i]中的最小值是否>=s[i+1]
    hh = 0, tt = -1;
    for (int i = 1; i <= n * 2; ++ i)
    {
        if (hh <= tt && q[hh] < i - n + 1) ++ hh;
        while (hh <= tt && s[q[tt]] >= s[i]) -- tt;
        q[ ++ tt] = i;
        if (i > n && s[q[hh]] >= s[i + 1]) st[i - n] = true;  // ps:i最终是窗口扩到的位置
    }                                                         //    起点在i-n+1, 但是i-n+1记录的是他到起点的值
                                                              //    所以最终起点 i-n 出发
    for (int i = 1; i <= n; ++ i) puts(st[i] ? "TAK" : "NIE");
    return 0;

}                                                             

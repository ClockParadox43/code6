// 该题是对DP典型的优化
//     f[i]: 1~i, 且点燃第i个烽火台的所有方案
// 最小代价: 最小代价

#include <iostream>

using namespace std;

const int N = 2e5 + 7;

int n, m, hh, tt;
int w[N], q[N], f[N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) cin >> w[i];
    
    f[0] = 0; // 考虑前0个烽火台, 代价为0

    // 1) 先记录i位置的代价
    // 2) 将之前队尾的代价和当前队尾的代价对比
    //    如果当前队尾代价更小, 就将之前的队尾弹出
    // 3) 再将当前位置加入队尾
    // 
    // 以i结尾的f[i], 滑动窗口的区间是[i-m, i-1], 
    // 单调队列维护的是该区间的最小值, 由于滑动窗口不包含i, 
    // 因此f[i]需要在while上方进行更新
    for (int i = 1; i <= n; ++ i)
    {
        // i-m:因为是从1开始计算的所以不需要+1
        if (hh <= tt && q[hh] < i - m) ++ hh;       // 如果队头的下标在窗口外就弹出
        f[i] = f[q[hh]] + w[i];                     // hh:最小代价, 当前代价等于队头代价加上当前代价
        while (hh <= tt && f[q[tt]] >= f[i]) -- tt; // 如果队尾的代价大于当前的代价, 替换掉
        q[ ++ tt] = i;
    }
    
    int res = 1e9;
    for(int i = n - m + 1; i <= n; ++ i) 
        res = min(res, f[i]);
    cout << res << endl;
    return 0;
}

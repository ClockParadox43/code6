// 有n个任务排成一个序列, 顺序不得改变, 其中第i个任务的耗时为ti, 费用系数为ci
// 现需要把该n个任务分成若干批进行加工处理
// 每批次的段头, 需要额外消耗S的时间启动机器, 每一个任务的完成时间是所在批次的结束时间
// 完成一个任务的费用为:从0时刻到该任务所在批次结束的时间t乘以该任务费用系数c
// (S+t1+..tn)(c1+..+cn)

// 分析:当每一批任务开始时, 会增加启动时间S, 
//      一旦在某批任务开始时增加启动时间, 有S影响之后批次的所有任务的完成时刻
//   解:所以我们可以将S对未来的影响提前先算掉->"费用提前计算"
//     1) 将S对后面每个区间的影响提前累加至当前的区间中去
//
//      那么S对后面每个区间总共的影响是多少?
//      让后面任务所有的花费全部增加S(c1+..+cn)

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;
const int N = 5010;

int n, s;
int sumt[N], sumc[N];   // sumt:耗费时间的前缀和, sumc:耗费代价的前缀和
ll f[N];
int q[N];

int main()
{
    cin >> n >> s;
    for (int i = 1; i <= n; ++ i)
    {
        int t, c; cin >> t >> c;
        sumt[i] = sumt[i - 1] + t;
        sumc[i] = sumc[i - 1] + c;
    }
    memset(f, 0x3f, sizeof f);
    f[0] = 0;           // 前0个任务的总划分方案

    // 状态表示f[i]:
    //   集合:前i个任务分批次的所有方案
    //   属性:min花费
    // 状态计算:
    //      以上一批任务的最后一个任务作为划分依据, 设上一批最后一个任务为j
    //      则以i作为最后一批任务,范围: j+1..i <= j <= i-1
    //
    // 不确定部分:前j个任务的划分方案, 对应状态f[j], 处理了从1..j的所有方案 
    //   确定部分:j+1..i, 假设任务花费时间与费用的前缀和分别为sumT,sumC
    //            则确定部分所需花费为 sumTi * (sumCi - sumCj), 与启动时间带来的花费 s * (sumCn - sumCj)之和
    //            ci-cj(j+1..i), cn-cj(j+1..n) (后面所有的花费之和)
    
    for (int i = 1; i <= n; ++ i)     // 这批物品到 i 结束
        for (int j = 0; j < i; ++ j)  // 上批物品到 j 结束
            f[i] = fmin(f[i], f[j] + 
            (ll)sumt[i] * (sumc[i] - sumc[j]) + (ll)s * (sumc[n] - sumc[j]));
    cout << f[n] << endl;
    return 0;
}
```c++
01背包:
时间复杂度 O(nm)
本题求01背包的最佳方案数, 那么定义两个数组: f[N],cnt[N]
f[i]: 用来存储背包容积为i时的最佳方案的总价值
cnt[i]: 为背包容积为i时总价值为最佳的方案数
```
```c++
先初始化所有的 cnt[i] 为 1, 因为背包里什么也不装也是一种方案

外层循环 n 次，每次读入新物品的 v,w
求出装新物品时的总价值, 与不装新物品时作对比

如果装新物品的方案总价值更大, 
那么用 f[j−v]+w 来更新 f[j], 用cnt[j−v]更新cnt[j]
如果总价值相等, 那么最大价值的方案数就多了cnt[j−v]种
```

###一维代码
```c++
#include <iostream>

using namespace std;
const int N  = 1010, mod = 1e9 + 7;

// 从0个物品里面选, 在背包容量为j的条件下, 得到f[0][j]的方案数目.
// 由于是0个物品, 所以f[0][j]=0,由于我们什么都不选, 这也是一种方案, 
// 所以我们初始化为1
int n, m;
int f[N], cnt[N];

int main()
{
    cin >> n >> m;
    for (int i = 0; i <= m; ++ i) cnt[i] = 1;
    for (int i = 1; i <= n; ++ i)
    {
        int v, w; cin >> v >> w;
        for (int j = m; j >= v; -- j)
        {
            int val = f[j - v] + w;     // 如果小于直接不用转移
            if (val > f[j])
            {
                f[j] = val;
                cnt[j] = cnt[j - v];
            }
            else if (val == f[j])
                cnt[j] = (cnt[j] + cnt[j - v]) % mod;
        }
    }
    cout << cnt[m] << endl;
    return 0;
}
```
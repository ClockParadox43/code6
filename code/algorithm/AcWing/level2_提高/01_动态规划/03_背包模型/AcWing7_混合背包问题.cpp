// 因为只限制了从前i个物品中选, 且总体积不超过j, 所以不需要考虑前i件物品的"类型是什么"
// 在状态计算的时候只需要用到的第i件物品是什么, 所以我们只需要考虑第i件物品的类型
// 所以我们可以根据"第i个物品的类型"来判断应该使用状态转移方程, 来使用相应的方程做计算
// 其余都一样
#include <iostream>
#include <cstring>

using namespace std;

const int N = 1010;

int n, m;
int f[N];

// si=−1: 表示第 i 种物品只能用1次   -> 01
// si=0 : 表示第 i 种物品可以用无限次 -> 完全
// si>0 : 表示第 i 种物品可以使用 si 次 -> 多重
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; ++ i)
    {
        int v, w, s; cin >> v >> w >> s;
        if (!s)         // 如果s为0就是完全背包 
            for (int j = v; j <= m; ++ j) 
                f[j] = max(f[j], f[j - v] + w);
        else
        {
            // 01和多重一起做
            // 将多重背包二进制优化
            // 就变成多个01背包
            // 01背包是一种特殊的多重背包
            if (s == -1) s = 1;
            
            // 如果是01就看做多重
            // 如果是多重就进行二进制优化
            for (int k = 1; k <= s; k *= 2)     // 拿到打包后的物品后直接枚举一遍
            {
                for (int j = m; j >= k * v; -- j)
                    f[j] = max(f[j], f[j - k * v] + k * w);
                s -= k;
            }
            // 如果有剩余物品再次循环一下
            if (s)
                for (int j = m; j >= s * v; -- j)
                    f[j] = max(f[j], f[j - s * v] + s * w);
        }
    }
    cout << f[m] << endl;
    return 0;
}
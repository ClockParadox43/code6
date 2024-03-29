// ps:求的是 最优选法的方案数
// 求最优解的方案书, 其实等价于求最短路径的条数
//      如何判断 - 所有能走到某个点的路径当中判断哪些路劲的长度最短
//         A ---> B
//       ↗        ↘
//      s -> C -> D -> e
//       ↘ _______↗
//         E 
// 
//      例: 假设最终我们要去 e 点, 那就判断能走到e点的那些路径, 
//          点B,D,E都能走到e点, 假设 点B,D 是能够到 点e 的最短路径, 
//          那么我们就累加上从起点能走到 点B,D 的这些路径的条数
//
// 这是在图论中求最短路径的条数的方案的解法
// 来到DP中也是一样的
// 定义一个数组 g[i,j]:代表能取到f[i,j]最大值的方案数
// 分析:
//      f[i,j]转移方程: 不选当前第i个物品: f[i-1,j], 选当前第i个物品: f[i-1,j-v]+w
//      1.左边大, 那么 g[i,j] 就从 g[i-1,j] 转移过来
//      2.右边大, 那么 g[i,j] 就从 g[i-1,j-v] 转移过来
//      3.如果一样大, 那么 g[i,j] 就累加上两边的方案数 g[i-1,j] + g[i-1,j-v]
//
// 因为第i层只和第i-1层有关, 所以g[]可以使用一维
// 
// 状态表示g[i,j]:体积恰好是j的方案数
// 这里是恰好: 转移时子集重合的, 可能需要容斥原理
#include <iostream>
#include <cstring>

using namespace std;

const int N = 1010, mod = 1e9 + 7;

int n, m;
int g[N];
int f[N];

int main()
{
    cin >> n >> m;
    memset(f, 0xcf, sizeof f);
    f[0] = 0;
    g[0] = 1;
    for (int i = 0; i < n; ++ i)
    {
        int v, w; cin >> v >> w;
        for (int j = m; j >= v; -- j)
        {
            int maxv = max(f[j], f[j - v] + w);
            int cnt = 0;
            
            // 为什么一个是赋值一个是累加?
            //      当前这个状态如果能由上一层的某个状态转移过来的了的话,
            //      就说明之前更新这个状态的点不是最优的, 那么我们就不能再将其算作一种选法了
            //      所以就不能是+=, 而必须是直接赋值
            // 
            //      相当于有两个集合, 一个集合选当前的物品, 一个集合不选, 然后我们要求的是两个集合的最大值, 以及最大值的元素数 
            //      那么如果左边集合的最大值大于右边集合的最大值, 那最大值的元素数就等于左边集合最大值的元素数
            //      反之就是右边集合的元素数. 如果左右两边最大值相等, 那么就应该是左右两个集合中取最大值的元素的个数之和
            
            if (maxv == f[j]) cnt = g[j];
            if (maxv == f[j - v] + w) cnt = (cnt + g[j - v]) % mod;
            // 注意!!!要先对比好后才能更新
            f[j] = maxv, g[j] = cnt % mod; 
        }
    }
    // 因为恰好是j, 体积越大价值越多, 体积恰好的话不一定是最值 
    // 所以还需要再求一遍组大值
    int res = 0;
    for (int i = 1; i <= m; ++ i)
        if (f[i] > f[res]) res = i;
    
    // 找到相等的方案数
    int sum = 0;
    for (int i = 0; i <= m; ++ i)
        if (f[i] == f[res]) sum = (sum + g[i]) % mod;
    cout << sum << endl;
    return 0;
}
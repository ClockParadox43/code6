// 优化多重背包:
// 方程展开:
//      f[i,j] =     f[i-1,j], f[i-1,j-v]+w, f[i-1,j-2v]+2w...f[i-1,j-sv]+sw
//      f[i,j-v] =             f[i-1,j-v],   f[i-1,j-2v]+w... f[i-1,j-sv]+(s-1)w, f[i,j-(s+1)v] + sw
//                                                                                f[i,j-sv-v] + sw  
// 1) f[i,j] 是从 0 开始的
//    f[i,j-v] 是从 1 开始的, 因为 f[i,j-v] 必须减掉一个 v
//    但是当 k=0 的时候, f[i,j-v*0] == f[i,j]
//    所以 f[i,j-v] 是从 1 开始的
// 
// 2) 因为多出一项(当某一件物品 i, 全部拿满但是依旧小于当前体积(v[i]*k < j)的情况)
//    所以不能用完全背包问题优化的思路  
// 
// 思路(二进制优化方式):
// 假设 S=200, 因为任何数都可以由若干指数不同的 2 的次幂组成, 所以不需要一一枚举
// 只需要枚举二进制位即可: 1 2 4 8 16 32 73
// 枚举到 128 总和会超出 200, 所以用取 73 即可, 就可以凑出 0~200 中的所有数 
// 每一种物品的打包都可以看做 "01背包" 问题中的物品, 因为只能选择一次, 其实就是用 7 个新物品来表示原来第 i 个物品
// 枚举新的物品选或不选就可以拼凑出原来物品所有的方案
// 原来要枚举 200 次(n) 现在只要枚举 7 次(logn), 因此得出了一个 logn 的做法
// 
// 从例子中抽象出规律实现成代码:
//
// 证明:
// S
// 1 2 4 8 ... 2^k, C
// C < 2^(k+1)
// 用倍增的思想可以凑出 0~2^(k+1)-1 中的数 
// 0~2^(k+1)-1 中的任何数 + C 后, 就可以凑出 C~2(k+1)-1 中的任何数
// 那么从 0~2^(k+1)-1 中的数和 C~S 中的数, 他们的并集是不是 0~S (是的话就代表没有空隙, 也就是可以凑出)
// 其实就是问 C 是否 > 0~2^(k+1)
// 如过不是的话就是中间有缝隙, 也就拼凑不出来
// 其实前面已经说过 C < 2(k+1), 所以可以凑出
//
// 时间复杂度分析:
// 如过第 i 个物品是 s[i] 个, 那么就把这个物品拆成 logs[i] 个
// 再对新的物品做一遍 "01背包问题" 即可
// 优化前的时间复杂度为 n v s, 3 重循环, 也就是说可以把时间复杂度优化成 n v logs
// 该题数据范围:
// 0 < N ≤1000
// 0 < V ≤ 2000
// 0 < vi,wi,si ≤ 2000
// 1000 * 2000 * log2000 ≈ 2*10^7 < 10^9

#include <iostream>
#include <algorithm>

using namespace std;


const int N = 25000, M = 2010;          // 物品个数最多是 1000*log2000, 所以 N = 25000

int n, m;
int v[N], w[N];
int f[N];

// 每次将一组物品{v,w,s}分解开, 将 k 个第 i 个物品打包在一起, 只要 k <= s 就可以分          
// 1) 将 k 个物品打包在一起 
//    k 个物品打包在一起体积就是 a * k
//    价值就是 b * k
 // 2) k *= 2, 因为任何数都可以由若干指数不同的 2 的次幂组成, 所以只要求 k^2
//    cnt 是每个物品的编号     
int main()
{
    scanf("%d%d", &n, &m);
    
    int cnt = 0;
    for (int i = 1; i <= n; ++ i)
    {
        int a, b, s; scanf("%d%d%d", &a, &b, &s);
        int k = 1;
        while (k <= s)
            ++ cnt, w[cnt] = k * a, v[cnt] = k * b, s -= k, k *= 2;
        
        if (s > 0)
            cnt ++, w[cnt] = s * a, v[cnt] = s * b;
    }
    
    for (int i = 1; i <= cnt; ++ i)
        for (int j = m; j >= w[i]; -- j)
            f[j] = max(f[j], f[j - w[i]] + v[i]);
            
    printf("%d", f[m]);
    return 0;
}

// Hamiliton 路径: 0~n-1 补充不漏每个点恰好经过一次
// 求起点到终点的最短 Hamiliton 路径
// 暴力全排列时间复杂度: o(n!*n)
//
// 状态表示:所有从 0~j, 走过的所有点存在 i 中(状态压缩)
//     集合:集合中的所有路径最终都要从 0 走到 i, 用走到 j 的倒数第二个点 k 来进行划分
//          因为 k~j 的权重是固定的, 也就是说只要求 0~k 的最短距离最后加上到 k~j 的距离
//          f[i][j] = min(f[i][j], f[i ^ (1<<j)][k] + w[k][j]
//
// 以上转移方程, w 数组为权值, 也就是w[k][j]是 k 点到 j 点的权值
// i^(1<<j)的意思是, i 异或 1右移j位, 具体来说就是i这个方案集合 xor 10……0,(其中1的位置在第j位)。
// i 表示的是二进制的路径, 1 表示走到了哪个点, 0 表示没有走到那个点, 那么 ^ 表示的就是除去那位的状态, 同位 0.
//
// 状态计算: f[i,j] 所有从 0 走到 i, 经过的点是 j 并且倒数第二个点是 k, 这样的一个方案
//        _______________
//       |_1_|_2_|...|n-1|

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 20, M = 1 << N;

int n;
int w[N][N];
int f[M][N];        // f[i,j] i 存的时状态

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i )
        for (int j = 0; j < n; ++ j )
            scanf("%d", &w[i][j]);
    
    // 初始化: 走过的所有点只有 0 这一个点
    memset(f, 0x3f, sizeof f);
    
    // f[0][0] 状态是非法, f[0][0] 表示没有走过任何一个点的状态但是到了 0 号点
    // f[1][0] 表示只经过了起点 0 (i 只有第 0 位为 1)  
    f[1][0] = 0;

    // 第一层循环枚举 i 的所有情况 (每种情况用二进制位表示)
    // 第二层循环表示 j 走到那个点
    // 第三层循环枚举所有 k 能转移到 j 的点, 求已 k 为终点的最短距离
    for (int i = 0; i < 1 << n; ++ i ) 
        for (int j = 0; j < n; ++ j )   
            if (i >> j & 1)                     // 该转态 i 包含 j 这点, 才能进行下一步判断
                for (int k = 0; k < n; ++ k )   // 枚举能到达 j 的点 k (首先, i>>j 一定是1, 那么1<<j那么多位也一定是1)
                    if (i - (1 << j) >> k & 1)  // 如果 1^(1<<j) 这个状态的第 k 位是 1 (倒数第 2 步来到 点 k 的情况) 
                    {
                        // 想要从 k 转移过来, 那么 i 除去点 j 得有 k 这个点(i-(1<<j))
                        // >> k 位: 因为 1 状态代表来过, 所以 >> k 位 & 1, 就代表有这个点
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + w[k][j]);
                    }

    // 走完了所有点的答案, 因为从 0 开始没有到达第 n 位
    cout << f[(1 << n) - 1][n - 1] << endl;
    return 0;
}
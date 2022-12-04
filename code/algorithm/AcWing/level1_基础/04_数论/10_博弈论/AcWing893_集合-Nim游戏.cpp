// 当前的 SG(x) 等于我所有能到的 SG 的值, 该集合中不存在的最小值
// SG(x) = mex(SG(y₁), SG(y₂) ,..., SG(yₖ))
//
// 1) SG(终点) = 0
// 2) 如果当前所有局面异或起来是 0 的话, 那么下一步变化一定不是 0  
//    如果当前所有局面异或起来不是 0, 那么下一步变化一定是 0  
// 
// 1) 当 SG(Gi) = 0 时, xor = 0, 显然先手必败
// 2) 当 xor = x ≠ 0 时, 因为肯定存在一个 SG(xi)^x < SG(xi), 而根据 SG() 的性质1可知, SG(k)
//    可以走到 0~k-1 的任何一个状态, 因此 SG(xi) -> SG(xi)^x, 于是使得 xor = 0 
//    (它每次都能异或得到一个比自己更小的数, 所以最终它自己可以变成 0)
#include <iostream>
#include <cstring>
#include <unordered_set>

using namespace std;

const int N = 110, M = 10010;
int n, m;
int f[M], s[N];     // s[] 存储的是可供选择的集合, f[] 存储的是所有可能出现过的情况的 sg 值

// x: 第 i 堆石子的数量
// 时间复杂度 m^n
int sg(int x)
{
    if (f[x] != -1) return f[x];    // 记忆化搜索, 如果f[x]已经被计算过, 则直接返回
    
    // 因为这题中较大堆的拆分情况独立于较小堆, 因此有别于 894, 拆分 -Nim, 这里的S必须开成局部变量
    // 局部化结果:同一层的可以使用到对应 S, 否则再另外的栈帧中
    unordered_set<int> S;   // 用一个哈希表来存每一个局面能到的所有情况, 便于求mex, 存储当前局面能走到哪些数

    for (int i = 0; i < m; ++ i )
    {
        int choose = s[i];
        // 如果可以减去s[i], 则添加到S中
        if (x >= choose) S.insert(sg(x - choose));    // 先延伸到终点的 sg 值后, 在从后往前排查所有数的 sg 值
        // 存储上一层走到的最小的自然数, 然后判断当前层是否可以走到(有序的)
    }

    // 流程:
    //  1) 将每个 x 存到 S 中去
    //  2) 如果自然数 i 在 S 中没有出现, 存储 x 对应的最小没有出现的自然数到 f[], 再返回 

    for (int i = 0; ; ++ i ) // 求 mex(), 即找到最小并不在原集合中的数
        if (!S.count(i)) return f[x] = i;   // 循环完后可以进行选出最小的没有出现的自然数进行操作
}

int main()
{
    scanf("%d", &m);    // m:可选集合中数的个数
    for (int i = 0; i < m; ++ i ) scanf("%d", &s[i]);

    memset(f, -1, sizeof f);    // 初始化 f 均为 -1, 方便在 sg 函数中查看 x 是否被记录过
    
    scanf("%d", &n);    // n:n 个整数, 表示第 i 堆石子的数量
    int res = 0;
    for (int i = 0; i < n; ++ i )   
    {
        int x; scanf("%d", &x);
        res ^= sg(x);           // 观察异或值的变化,基本原理与Nim游戏相同
    }

    if (res) puts("Yes");
    else puts("No");

    return 0;
}
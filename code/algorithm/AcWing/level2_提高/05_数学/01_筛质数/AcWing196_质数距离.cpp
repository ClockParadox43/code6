// 题目大意: 你需要在闭区间 [L,U] 内找到距离最近的两个相邻质数 C1 和 C2 (即 C2-C1 最小)
//          如果存在距离相同的其他相邻质数对, 则输出一对 
//          还需输出最远的两个响铃质数 D1,D2 (即 D1-C2 最大), 存在则输出
//
// 例:[1,10] -> 2,3,5,7
//    (2,3), (3,5), (5,7)
//      1      2      2
// ans:(2,3)
//
// 1) 范围较小: 1≤L≤R≤10⁷
//    线性筛出所有质数, 然后扫一遍即可
//  
// ps : 线性筛只能从 1~n 筛
// 2) 范围较大: 1≤L≤R≤10³¹-1
//    - 一个数如果是合数, 必然存在两个因子: d, n/d
//      ∵ d ≤ n/d => d ≤ √n
//      因此必然存在一个小于等于 √n 的因子(大于根号 n 的质因子, 一个合数中只存在一个)
//
//    - 找出 x∈[L,R], 且 x 是合数, 则一定存在 P ≤ qrst(2³¹ - 1) (<50000), 使得 p 能整除 x, 其中 p < x
//      反过来, 如果 1~50000 之间存在一个小于 x 且 整除 x 的质因子, 那么 x 一定是合数
//
// 如果是合数必然存在质因子, 
//  1) 找出 1~50000 中的所有质因子
//  2) 对于 1~50000 中的每个质数 p, 找出 [L,R] 区间 p 的倍数筛掉(至少 2 倍), 做一遍埃氏筛即可
//
// - L~R 之间的每一个数, 如果是合数的话, 必然存在一个小于等于 √L 的质因子, L 的最大值是 2*10⁹
//   因此预处理出 1~50000 之间的所有质数, 此时 L~R 之间如果存在一个合数必然存在 1~50000 之间的一个质因子
//   将那个合数筛掉即可   
// 
// 也就是说 L~R 之间的任何一个数, 如果是质数的话, 也就不存在 1~50000 之间任何一个数的质因子
// 筛掉  1~50000 质数的倍数剩下的就是质数
//
// 时间复杂度: [L,R] 中最多有 10⁶/p(1~50000中的质数) 个倍数
//           10⁶(1/p + 1/p+1 + 1/p+2 + .. + 1/pn) -> O(N)

#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;
const int N = 1000010;

int primes[N], cnt;
bool st[N];

void init(int n)
{   
    memset(st, 0, sizeof st);
    cnt = 0;
    // 因为出题人偷懒, primes[] 和 st[] 会被复用, 所以每次要重复预处理下
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] * i <= n; ++ j )
        {
            // 筛掉 i * p[j] 的合数, p[j] 作为最小质数
            st[i * primes[j]] = true;       
            if (i % primes[j] == 0) break;

            // i % p[j] != 0 说明 p[j] 是小于 i 的最小质因子的质因数
            // 因为 i % p[j] == 0, 也就是说 i 只会被自己的最小质因子筛掉
            // 同时也是 p[j] * i 的最小质因子 (因为只会从小到大枚举)
        }
    }
}

int main()
{
    int l, r;
    while (cin >> l >> r)
    {
        init(50000);
        memset(st, 0, sizeof st);

        // 枚举 1~50000 之间所有数的质数, 因为答案是在 [L,R] 这个范围内, 找到大于等于 L 的最小的 P 的倍数 p₀
        // 内层循环 for (j = p₀; j <= r; j += p₀)
        // 埃氏筛掉所有数的合数, 从 p₀ 的二倍起筛, 每次加等 p₀ 的倍数
        // ⌈l/p⌉ 得到 l 是 p 的多少倍, 有了 p 的倍数再乘 p 就是我们要求的值 (大于等于 L 的最小的 p 的倍数)
        // ⌈l/p⌉ = ⌊l+p-1/p⌋ 
        for (int i = 0; i < cnt; ++ i ) 
        {
            LL p = primes[i];   // p 找到的是质数
            for (LL j = max(p * 2, (l + p - 1) / p * p); j <= r;  j += p) 
                st[j - l] = true;       // 因为下标差距过大所以用偏移量来存储, j += p 找到的是倍数
        }
        // st[]: 倍数:true, 素数:false
        
        // 统计这个范围的所有质数
        // i 的范围小于质数范围 (r - l 偏移量)
        cnt = 0;
        for (int i = 0; i <= r - l; ++ i )
            if (!st[i] && i + l >= 2)     // !st[i]:没有被标记的就是质数
                primes[cnt ++ ] = i + l;  // i + l:将之前减去的偏移量加回来, 还原回质数
        
        // 这个范围内不足两个质数就输出无解
        if (cnt < 2) puts("There are no adjacent primes.");
        else 
        {
            // 否则就输出答案, 一个一个枚举找到最小的质数对
            // minp:最小的一对, maxp:最大的一对
            // 2 3 5 7
            int minp = 0, maxp = 0;
            for (int i = 0; i + 1 < cnt; ++ i )
            {
                int d = primes[i + 1] - primes[i];             // 下一个质数减去当前质数 
                if (d < primes[minp + 1] - primes[minp]) minp = i; // 遇到更小的差就替换
                if (d > primes[maxp + 1] - primes[maxp]) maxp = i; // 遇到更大的差就替换
            }

            printf("%d,%d are closest, %d,%d are most distant.\n",
                primes[minp], primes[minp + 1],
                primes[maxp], primes[maxp + 1]);
        }
    }

    return 0;
}
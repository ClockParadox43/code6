// 对于给定的整数 a, b 和 d, 有多少正整数对 x,y, 满足 x≤a, y≤b, 并且 gcd(x,y)=d
// 过程看配图

#include <iostream>
#include <cstring>

using namespace std;

const int N = 500010;

typedef long long LL;

int primes[N], cnt;         // 线性筛
bool st[N];         
int mobius[N], sum[N];      // 莫比乌斯函数, 前缀和

// 线性筛法: 求 每个数字对应自己的 mobius 函数 
// 每个合数会被自己最小质因子筛掉
void init(int n)
{
    mobius[1] = 1;
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i])     // 没筛过就代表是质数
        {
            primes[cnt ++ ] = i;
            mobius[i] = -1;        // 因为里面有奇数个质因子, 所以 mobius 函数是 -1(每个质因子只出现奇数次)
        }
        for (int j = 0; primes[j] * i <= n; ++ j )
        {
            int t = primes[j] * i;      // 合数(i*p[j]) 被自己最小质因子筛掉
            st[t] = true;               
            if (i % primes[j] == 0)     // p[j] 是 i 的最小质因子, i 是个合数, mobius 函数记作 0(某个质因子个数大于 1)
            {                           // p[j] 只能筛到 i, 说明 p[j] 重复出现 
                mobius[t] = 0;     
                break;
            }
            mobius[t] = mobius[i] * -1; // 因为 p[j] 这个质因子只有 1 个, 那么其他 mobius 函数质因子有没有大于 1, 取决于 i 的质因子的个数
        }                               // 1 (有偶数个不同质因子, 且只出现一次)
    }

    // 求 mobius 函数的前缀和
    for (int i = 1; i <= n; ++ i ) sum[i] = sum[i - 1]  + mobius[i];
}

int main()
{
    init(N - 1);    // 初始化 1~500000 中所有数的 mobius 函数是多少
    
    int T; scanf("%d", &T);
    while (T -- )
    {
        int a, b, d; scanf("%d%d%d", &a, &b, &d);
        a /= d, b/= d;  // d = gcd(a,b), 相当于求 gcd(x', y') = 1
        int n = min(a, b);
        LL res = 0;     // 答案是 n 方级别, 所以可能会爆 int
        for (int l = 1, r; l <= n; l = r + 1)
        {
            r = min(n, min(a/(a/l), b/(b/l)));       // g(x) = x/x/i : 回传当前一样的一段中(整除导致取整, 导致有一样的数出现), 能跳到的下标最大的
            res += (sum[r] - sum[l - 1]) * (LL)(a/l) * (b/l);   // 最终推出的式子
        }
        printf("%lld\n", res);
    }
    return 0;
}


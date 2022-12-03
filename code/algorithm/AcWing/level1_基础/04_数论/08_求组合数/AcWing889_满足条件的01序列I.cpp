// 给定 n 个 0 和 n 个 1, 它们将按照某种顺序排成长度为 2n 的序列, 
// 求它们能排列成的所有序列中, 能够满足任意前缀序列中 0 的个数都不少于 1 的个数的序列有多少个
//
// 任何一条从 (0,0) -> (n,n) 经过红线的路径, 都对应一条从 (0,0) -> (n-1,n+1) 的路径
// ans = C(2n,n) -> C(2n,n-1) = C(2n,n)/n+1    
//
// 该定理的应用: 每一条路径都可以转化成一个路径对应一个方案数, 不同路径对应不同排列, 很多问题的方案数都是卡特兰数, 应用很广泛
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 200010, mod = 1e9 + 7;

int n; 
int fact[N], infact[N];

int quick_pow(int a, int k)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL)res * a % mod;
        a = (LL)a * a % mod;
        k >>= 1;
    }
    return res;
}

void init()
{
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; ++ i )
    {
        fact[i] = (LL)fact[i - 1] * i % mod;
        infact[i] = (LL)infact[i - 1] * quick_pow(i, mod - 2) % mod;
    } 
}

int main()
{
    int n; scanf("%d", &n);
    init();
    int ans = (LL)fact[2 * n] * infact[n] % mod * infact[n] % mod * quick_pow(n + 1, mod - 2) % mod;
    printf("%d\n", ans);
    return 0;
}
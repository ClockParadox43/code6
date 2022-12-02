// 1) 上一道题:10w 组询问, 1≤b≤a≤2000 询问次数非常多用打表
// 2) 1w 组:1≤b≤a≤10^5
//    C(a,b) = a!/(a-b)! * b!, 阶乘用 fact[i] = i! mod 10^9 + 7 表示
//    因为是除法, 不是很好取整, 所以对于 a!/(a-b)! * b! 找到它的逆元
//    即 infact[i] = (i!)^-1 * mod % 10^9 + 7
// 
//    用 infact(i) 表示 i! 的逆元, 快速幂求逆元
// C(a,b) = fact(a!) * infact(b-a!)^-1 * infact(b!)^-1


#include <iostream>

using namespace std;

const int N = 1e5 + 10, mod = 1e9 + 7;
typedef long long LL;

LL fac[N], infac[N]; // fac:阶乘 mod p 的值, 逆元 mod p 的值

int quick_pow(int a, int k, int p)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

int main()
{
    int n; scanf("%d", &n);

    fac[0] = infac[0] = 1;
    for (int i = 1; i <= 1e5; ++ i )
    {
        fac[i] = fac[i - 1] * i % mod;  // 求阶乘
        infac[i] = (LL)infac[i - 1] * quick_pow(i, mod - 2, mod) % mod; // 求逆元
    }

    while (n -- )
    {
        int a, b; scanf("%d%d", &a, &b);
        printf("%lld\n", (LL)fac[a] * infac[b] % mod * infac[a - b] % mod);
    } 

    return 0;  
}
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 2010, mod = 100003;

int fact[N], infact[N]; // fac:阶乘 % mod 的值, 逆元 % mod 的值

int qmi(int a, int k)
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

// C(a,b) = a! / b!*(a!-b!) 
int C(int a, int b)
{
    if (a < b) return 0;
    return (LL)fact[a] * infact[a - b] % mod * infact[b] % mod;
}

int P(int a, int b)
{
    if (a < b) return 0;
    return (LL)fact[a] * infact[a - b] % mod;
}

int main()
{
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; ++ i )
    {
        fact[i] = (LL)fact[i - 1] * i % mod; // 阶乘 % mod
        infact[i] = (LL)infact[i - 1] * qmi(i, mod - 2) % mod;  // 逆元 求出对于 a!, infact(b-a!)^-1 * infact(b!)^-1
    }

    int a, b, c, d, k; cin >> a >> b >> c >> d >> k;
    
    // 最后推出的结果: C(b,i) * A(a,i) * C(d, k-i) * A(a + c - i, k-i)
    int res = 0;
    for (int i = 0; i <= k; ++ i )
        res = (res + (LL)C(b, i) * P(a, i) % mod * C(d, k - i) * P(a + c - i, k - i)) % mod;
    
    printf("%d\n", res);
    
    return 0;
}   
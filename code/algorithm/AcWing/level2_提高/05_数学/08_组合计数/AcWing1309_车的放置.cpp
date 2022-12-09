#include <iostream>

using namespace std;

typedef long long LL;

const int N = 2010, mod = 100003;

int fact[N], infact[N]; // fac:阶乘 % mod 的值, 逆元 % mod 的值

int main()
{
    fact[0] = infact[0] = 1;
    for (int i = 1; i < N; ++ i )
    {
        fact[i] = (LL)fact[i - 1] * i % mod;
        infact[i] = (LL)infact[i - 1] * qmi(i, mod - 2) % mod;
    }

    
}   
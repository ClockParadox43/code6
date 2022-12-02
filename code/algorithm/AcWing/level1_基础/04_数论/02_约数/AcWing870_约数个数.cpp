// 约数个数:
// 基于算数基本定理
// N = p1^α1 * p2^α2 * p3^α3...      
// 那么它的约数个数就是(α1+1)*(α2+1)*(α3+1)...
// 分解后的质因数的 k 次方, 就是 p1^0~p1^k, 都对应着不同的约数, 那么 (0,1,2 .. k) 就是约数个数  
// 将不同底数不同的指数相乘(不同指数代表不同的约数), 就是总的约数个数
// 12 = 2^2 * 3
// (2+1) * (1+1)
// 1) 先分解质因数
// 2) 将各个质因数的的指数累加在一起
// 3) 再将每个质因数的指数 + 1 连乘

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long LL;

const int mod = 1e9 + 7;

void test()
{
    // n 个数
    int n;
    cin >> n;

    unordered_map<LL, int> primes;    
    while(n -- )
    {
        // 枚举 x 的质因数
        LL x;
        cin >> x;
        
        // 枚举所有质因数, 不会枚举到合数, 因为该质因数有关的合数会被除尽
        for (LL i = 2; i <= x / i; ++ i )
            while (x % i == 0) x /= i, primes[i] ++ ; 
        if (x > 1) primes[x] ++ ;
    }
    
    LL res = 1;
    
    // 枚举所有的质因数
    // 取出所有质因数的指数 + 1 连乘
    for (auto prime : primes) res = res * (prime.second + 1) % mod;
    
    cout << res << endl;
}

int main()
{
    test();
    return 0;
}


// 给定一个整数 n, 求有多少正整数数对 (x,y) 满足 1/x + 1/y = 1/n!
//   1/x + 1/y = 1/n!
//    (x+y)/xy = 1/n!
// x·n! + y·n! = xy  
//        x·n! = xy - y·n!
//        x·n! = y(x-n!)
//           1 = y(x-n!)/x·n!
//         1/y = (x-n!)/x·n!
//           y = x·n!/(x-n!)    -> 也就是求有多少个 x 有多少种取值使得 y是一个正整数, x∈Z*
//
// y = x·n!/(x-n!) = (x+n!-n!)n!/x-n! 
//                 = xn!+n!^2-n!^2
//                 = (x-n!)n!/x-n! + n!^2/x-n!
//                 = n! + n!^2/x-n!
//
// 有多少个正整数的取值 x, 使得 n!^2/x-n! 是正整数, x-n!|n!^2
// 也就是说有多少个 x 的取值使得 x-n! 是 n!^2 的约数, 也就是求 n!^2 的约数个数
//
// 假设求出:   n! = p1ᶜ¹ - p2ᶜ² - ... - pnᶜⁿ
//         则 n!^2 = p1²⁽ᶜ¹⁾ - p2²⁽ᶜ²⁾ - ... - pn²⁽ᶜⁿ⁾
//
// 求约数个数公式: f(i) = f(2(c₁+1)) + f(2(c₂+1)) + ... + f(2(cₙ+1))
#include <iostream>

using namespace std;

typedef long long LL;
const int N = 1e6 + 10, mod = 1e9 + 7;

int primes[N], cnt;
bool st[N];

// 筛质数
void init(int n)
{
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] * i <= n; ++ j )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

// 假设求出:   n! = p1ᶜ¹ - p2ᶜ² - ... - pnᶜⁿ
//         则 n!^2 = p1²⁽ᶜ¹⁾ - p2²⁽ᶜ²⁾ - ... - pn²⁽ᶜⁿ⁾
//
// 求约数个数公式: f(i) = f(2(c₁+1)) * f(2(c₂+1)) * ... * f(2(cₙ+1))
int main()
{
    int n; scanf("%d", &n);
    init(n);

    int res = 1;
    // 枚举所有质数
    for (int i = 0; i < cnt ; ++ i )
    {
        int p = primes[i];    
        int s = 0;
        for (int j = n; j; j /= p) s += j / p;  // 算出所有倍数
        res = (LL)res * (2 * s + 1) % mod;      // f(i) = f(2(c₁+1)) * f(2(c₂+1)) * ... * f(2(cₙ+1))
    }
    
    printf("%d", res);

    return 0;
}
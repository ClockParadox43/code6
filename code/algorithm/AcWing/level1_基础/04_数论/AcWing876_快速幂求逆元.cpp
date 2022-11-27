// 乘法逆元的定义:
// 若整数 b, m 互质, 并且对于任意的整数 a, 如果满足 b|a, 则存在一个整数 x, 使得 a/b ≡ a*x (mod m) 
// 则称 x 为 b 的模 m 乘法逆元, 记为 b^-1 
// b 存在乘法逆元的充要条件是 b 与模数 m 互质, 当模数 m 为质数时, b^(m−2) 即为 b 的乘法逆元
// 
// 对于每个 a/b, 找到一个 x, 使得 a/b 和 ax(modm) 余数相同
// 将 x 叫做 modm 的逆元, 记作 b^-1
// 也就是把所有 a/b 的情况转化成 a * b^-1 的情况, 这个 b^-1 就是 a/b 的逆元
// 数论中除法不一定保证有整数, 但是乘法就很舒服, 同余可以作为唯一标记
//
// a / b ≡ a * x (mod m)
// 两边同时乘 b 可得 a ≡ a * b * x (mod m)
// 即 1 ≡ b * x(mod m)
// 同 b * x ≡ 1(mod m)
// 由费马小定理可知, 当 n 为质数时 
// b^(m-1) ≡ 1(mod m)
// 联系本方程(拆出一个 b 可得 b*b^(m-2) ≡ 1(mod m)) b*b^(m-2) ≡ 1, 所以 b 的逆元 x 为 b^(m-2)
// 故当 m 为质数时, b的乘法逆元 x = b^(m-2)
#include <iostream>

using namespace std;

typedef long long LL;

// m^k -> 此处 m 用 p 表示 
int qmi(int a, int b, int p)
{
    int res = 1 % p;
    for (; b; b >>= 1 )
    {
        if (b & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
    }
    return res;
}

// 若 b 是 m 的倍数, 则无解的, 因为 b 是 m 的倍数, 那么 b*x 也必定是 m 的倍数, 模 m 的余数为 0, 必定不为 1, 是无解的情况
// 若 b 不是 m 的倍数, 由于 m 是质数, 那么 b 与 m 是互质的, 由费马小定理可知, b^(m-1) ≡ 1 (mod m), 一定存在逆元, 一定有解
int main()
{
    int _ ; scanf("%d", & _ );
    
    while (_ -- )
    {
        int a, p;
        scanf("%d%d", &a, &p);
        if (a % p == 0) printf("impossible\n");
        else printf("%d\n", qmi(a, p-2, p));
    }
    
    return 0;
}
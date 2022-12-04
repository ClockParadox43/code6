#include <iostream>

using namespace std;

typedef long long LL;

// 1) 要求解的问题是使得 L|x个8
//    x个8 = 8 · (x个1) = 8 · (x个9)/9 = 8 · 10^x-1 / 9   
// 
// 2) 于是原问题就变成求解满足 9L|8(10^x-1) 的最小正整数 x
//    筛掉 9L 和 8(10^x-1) 的公因子
//    继续化简, 10^x-1 一定是 9..9, 和 9L 一样都有一个因子 9
//    那么我们缩小范围就筛掉 9L 和 8 的因子
//    由于 (9, 8) = 1, 所以我们可以求 (L, 8), gcd(L, 8) 记作 d
//  
// 3) 还是化简, 10^x -1 记作 A, 9L|8A 
//    又因为 gcd(8,9) = 1, 所以设 gcd(9L, 8) = gcd(L, 8) = 1
//    ps: d|L, 那么 d 也可以整除 L 的倍数
//    那么 8, 9, 9L 都有个最大公因数 d
//    则:
//       9L/d | 8/d·A
//      又因为 gcd(9L/d, 8/d) = gcd(L/d, 8/d) = 1
//      因为 8/d 和 9L/d, L/d 互质, 所以 8/d 也不能整除 L/d, 
//      因为和 9L 的最大公因子以消去, 8/d 也不能整除 9
//      所以只有 L/d 和 9 可以整除 A
//   所以就得到了 9L/d|A
// 
// 4) 将 9L/d 记作 C, C|(10ˣ - 1), 也就是 10ˣ ≡ 1 (mod C)
//    根据这样的同余方程, 定理: 最小的 x 一定是 phi(c) 的某个约数, 记作 x|phi(c)
//    
// 5) 10ˣ ≡ 1 (mod C) <=> (10ˣ, C) = 1 <=> (10ˣ)m + Cn = 1          ps: x 是未知数, 存在 x, m, n, 3 个未知数, 不能用扩展欧几里得
//    也就是说 10ˣ 和 C 互质, 如果不互质, 那么必定存在一个大于 1 的约数
//    那么左边必然可以整除 > 1 的约数
//    也就是说右边不可能等于 1, 因为 1 不能整除任何数, 这就矛盾了
//    所以 10 和 C 不互质无解
//
// 6) 最后枚举出所有 phi(c) 的所有约数, 求最消的 x
//
// 欧几里得算法
int gcd(LL a, int b)
{
    return b ? gcd(b, a % b) : a;
}

// 试除法求欧拉函数
// 筛除质数根据公式乘进 res 并返回
LL get_euler(LL c)
{
    LL res = c;
    for (int i = 2; i <= c / i; ++ i )     
    {
        if (c % i == 0)
        {
            int s = 0;
            while (c % i == 0) ++ s, c /= i;
            res = res / i * (i - 1);            
        }
    }
    if (c > 1) res = res / c * (c - 1);
    return res;
}

// 龟速乘 -> 求 a * b
LL qmul(LL a, LL b, LL c) 
{
    LL res = 0;
    while (b) 
    {
        if (b & 1) res = (res + a) % c;
        a = (a + a) % c;
        b >>= 1;
    }
    return res;
}

// 快速幂 -> 求 a^b
// 快速幂 两个乘法, 都是 10^10 级别, 所以会爆 long long, 用乌速乘乘上相乘的数 % c, 防止暴 long long
LL qmi(LL a, LL b, LL c) 
{
    LL res = 1;
    while (b) 
    {
        if (b & 1) res = qmul(res, a, c);
        a = qmul(a, a, c);
        b >>= 1;
    }
    return res;
}

int main()
{
    int T = 1;
    LL L;
    
    // 1) 求 9L|8(10^x-1) 的最小正整数 x, 筛掉 9L 和 8(10^x-1) 的公因数来求解
    //    根据第 2 步求出 gcd(L, 8), 记作 d
    // 2) 根据 (2) 和 (3) 我们得到最后化简为的式子 9L/d|A
    // 3) 将 9L/d 记作 C, 得到 C|10ˣ - 1 <=> 10ˣ ≡ 1 (mod C)
    //    根据 (4) 的定理求出 phi(c), 来得到最小的 x
    while (cin >> L, L)
    {
        int d = gcd(L, 8);      
        LL c = 9 * L / d;   // 将 9L/d 记作 C
        
        LL phi = get_euler(c); // phi(c), 来得到最小的 x

        LL res = 1e18;
        if (c % 2 == 0 || c % 5 == 0) res = 0;  // 判断 c 和 10 是否互质 (10 必须模 c 余 1)
        else
        {
            // 有解情况:
            //      - 定理: 最小的 x 一定是 phi(c) 的某个约数, 记作 x|phi(c)
            for (LL i = 1; i <= phi / i; ++ i )
            {
                if (phi % i == 0)
                {
                    // 如果 % c 是等于 1 的说明是满足要求的
                    if (qmi(10, i, c) == 1) res = min(res, i);          // 求 10^i 
                    if (qmi(10, phi / i, c) == 1) res = min(res, phi / i);  // 求 10^phi/i  求两个约数的 x
                }
            }
        }
        printf("Case %d: %lld\n", T ++ , res);
    }
    return 0;
}
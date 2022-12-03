#include <iostream>

using namespace std;

typedef long long LL;

// 用扩展欧几里得求出 ax + by = gcd(a, b) 的解
LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }
    LL x1, y1;
    LL res = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return res; 
}

int main()
{
    int n; scanf("%d", &n);
    
    bool has_ans = true;
    LL a1, m1; scanf("%lld%lld", &a1, &m1);

    // 读入后面的 n - 1 个方程
    // a₁k₁+ a₂k₂ = d           扩展欧几里得求出的
    // 
    //  原式
    //  x = k₁a₁ + m₁ (1)
    //                        =>  k₁a₁ + m₁ = = k₂a₂ + m₂  => k₁a₁ - k₂a₂ = m₂ - m₁ => 用扩展欧几里得可求出 k₁, k₂
    //  x = k₂a₂ + m₂ (2)
    // 
    // k₁a₁ + k₂a₂ = m₂ - m₁, 有解条件为 d|m₂-m₁
    for (int i = 0; i < n - 1; ++ i )
    {
        LL a2, m2; scanf("%lld%lld", &a2, &m2);

        // 合并方程, 先用扩展欧几里得算法求出系数
        LL k1, k2;
        int d = exgcd(a1, a2, k1, k2);
        if ((m2 - m1) % d)  // 无解 
        {
            has_ans = false; 
            break;
        }

        // y = (m2 - m1) / d, d|m2 - m₁
        // 也就是说 m2 - m1 是 d 倍数
        // 让 k₁, k₂ 分别扩大 y 倍, 则可以找到一个 k₁, k₂ 满足的 k₁a₁ + k₂(-a₂) = m₂ - m₁
        k1 *= (m2 - m1) / d;
        // 让 k 尽可能取小
        LL t = a2 / d;
        k1 = (k1 % t + t) % t;  // <=> k₁ = (k₁ % (a₂ / d)+ a₂ / d) % (a₂ /d);

        // 将 k₁ + k(a₂/d) 代入 x = k₁ + a₁ + m₁
        // 新的 x = (k₁ + k*a₂/d) * a₁ + m₁
        // k₁*a₁ +  k * a₁a₂/d + m₁
        // (k₁*a₁+m₁) + k[a₁,a₂]
        //   m1         a1
        m1 = a1 * k1 + m1;
        a1 = abs(a1 / d * a2); 
    }

    if (has_ans) cout << (m1 % a1 + a1) % a1 << endl;
    else cout << -1 << endl;
    return 0;
}
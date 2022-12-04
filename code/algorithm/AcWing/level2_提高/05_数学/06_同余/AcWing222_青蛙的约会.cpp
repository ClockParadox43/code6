#include <iostream>

using namespace std;

typedef long long LL;

int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
    {
        int x = 1, y = 0;
        return a;
    }

    int x1, y1; 
    int res = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return res;
}
 
int main()
{
    // b~a 的距离: b-a (米)
    //     A 追 B: m - n (速度)
    LL a, b, m, n, L; scanf("%lld%lld%lld%lld%lld", &a, &b, &m, &n, &L);
    
    // 设: 跳 x 次后 A 和 B 相遇
    // 1) 追了 (m-n)x 米, 是否可以相遇
    // 2) 判断 (m-n)x = b-a 这个等式是否相等
    // 3) 可能绕了很多圈, b-a + y·L
    // 4) (m-n)x = b-a + y·L
    //    (m-n)x + (-y)L = b - a => 扩展欧几里得
    //    也就是求 (m-n)x 和 (-y)L 求最小公倍数得到, x₀ 和 y₀ 个 d
    //    判断是解是否存在: d|b-a 为有解情况
    // 5) x 就是我们要求的解
    // 通解: x = x₀ + k⌊L/d⌋, y = y₀ + k⌊m-n/d⌋
    int x, y;
    LL d = exgcd(m - n, L, x, y);
    if ((b-a) % d) puts("Impossible");
    else
    {
        // 求出了等于 d 的一组解, 因为求的是最小公因数的一组解, 为了使等式成立, 所以还要扩大若干倍使得等式成立
        // (b - a) / d 得到是倍数, d 是结果, 并且更小了, 所以我们要知道缩小了几倍, 也就是原等式的结果 b - a
        // 用 (b-a)/d 得出缩小几倍
        x *= (b - a) / d;
        LL t = abs(L / d);  
        cout << (x % t + t) % t << endl;
    } 

    return 0;
}

// ax≡b(mod m) -> ax 除以 m 的余数是 b, 等价于求:
//          ax = my + b
//     ax - my = b
//   设: y' = -y
//          = ax = m*(-y) + b
//          = ax + my = b   -> 扩展欧几里得算法
// 因为是等价变形所以让 ax≡b(mod m) 有解, 等价于 ax + my = b 有解 
// 因为 gcd(a,m) = b , 所以对于任意的 x, y, ax + my 一定是 b 的倍数, 所以 b|ax, my|b 
// 特别地, 有 x, y 使得 ax + my = b, 要使这种情况发生最大也就一倍
// 
// 有解条件为 gcd(a,m)|b, 然后用扩展欧几里得求解即可
#include <iostream>

using namespace std;

typedef long long LL;

int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0) 
    {
        x = 1, y = 0; 
        return a;
    }
    int x1, y1, res;
    res = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return res;
}

int main()
{
    // 求 ax≡b(mod m), ax - my = b
    //                  y = -y'
    //                 ax + my = b -> gcd(a, m) = b
    // (a,m)|b 就有解
    int n; scanf("%d", &n);
    while (n -- )
    {
        int a, b, m; scanf("%d%d%d", &a, &b, &m);
        int x, y;
        int d = exgcd(a, m, x, y);
        if (b % d) puts("impossible");  // 因为 gcd(a,m)|b, 所以有余数一定无解 
        else printf("%d\n", (LL)b / d * x % m); // x 扩大若干倍然后 mod 到 m 范围内
    } 
    return 0;
}
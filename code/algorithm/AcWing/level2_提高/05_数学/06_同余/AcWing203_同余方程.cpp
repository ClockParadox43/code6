// 复习:
// 扩展欧几里得算法
// 
// 扩展欧几里得原理
//            (a,b) = d, 
//          ax + by = d
//            (a,b) = (b, a mod b) => 开始迭代的时候, 将 x,y 代入
//  xb + y(a mod b) = d 
//  xb + y(a - ⌊a/b⌋ * b) = d
//  xb + ya - by⌊a/b⌋ = d
// ay + b(x - y⌊a/b⌋) = d
// x' = y, y' = x - ⌊a/b⌋y
//
// 因为 a, b 是 (a,b), 所以 ax + by 一定是 (a,b) 的倍数, 那么 ax + by 能凑出的最小数就是 (a,b) 
// gcd(a, b) 记作 d
// 想求两个系数 x, y, 有 ax + by = d 
// 
// q: 
// ax mod c = b => ax = cy + b
// 
// 求关于 x 的同余方程 ax ≡ 1(mod b) 的最小正整数解
// ax ≡ 1(mod b) => ax % b = 1 % b 
// ∵ 1 % b = 1 
// ∴ ax % b = 1
// ∴ ax = by + 1  
// ∴ ax + (-b)y = 1 => 用扩展欧几里得求出 x₀, y₀
// 通解: x = x₀ + k(a/d), y = y₀ + k(b/d)
// 因为余数等于 1, 所以满足 x₀ + k(a/d) 必然不等于 0 
// ps:如果 x 等于 0, 0 乘任何数都是 0, ax = 0, ax % b 必然没有余数
// 然后, 满足 x₀ + k(a/d) 这种形式的正整数解就是 x % b  
#include <iostream>

using namespace std;

int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a; 
    }

    int x1, y1;
    int res = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1; 
    return res;
}

int main()
{
    // ax ≡ 1(mod b) => ax % b = 1 % b 
    // ∵ 1 % b = 1 
    // ∴ ax % b = 1
    // ∴ ax = by + 1
    // ∴ ax + (-b)y = 1 => 用扩展欧几里得求出 x₀, y₀
    // 通解: x = x₀ + k(a/d), y = y₀ + k(b/d)
    int a, b; scanf("%d%d", &a, &b);
    
    int x, y;  
    exgcd(a, b, x, y);
    
    // 此时已经求出了 x₀, 我们要求的是 x
    // 满足等式的最小正整数 = x mod b = (x₀ mod b + b) % b
    cout << (x % b + b) % b << endl;

    return 0;
}
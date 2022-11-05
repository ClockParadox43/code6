#include <iostream>

using namespace std;

// 指数的定义为, 只能被 1 和它自己整除
// 暴力: 自己是否能被整数, 2~n-1 一一枚举
// d|n : d 能够被 n 整除  例: 3|6, 4|20

// 1) 试除法
// 时间复杂度:O(n^2)-> TLE
void is_primeI()
{
    int m;
    scanf("%d", &m);
    
    while (m -- )
    {
        int n;
        scanf("%d", &n);
        
        bool flag = false; // 假设它不是质数, 如果最终能枚举到自己那就改为质数
        int i = 2;
        for (i = 2; i < n; ++ i )
            if (n % i == 0) break;
        
        if (i == n) flag = true;
        flag ? printf("Yes\n") : printf("No\n");
    }
}

// 如果 d|n 那么 n/d|n 也可以被 n 整除, d 和 n/d 都是 n 的约数  
// 
// 因为 d 和 n/d 都是成对出现的
// 所以可以只枚举每一对中较小(约数)的那个 d <= n/d, d^2 <= n, d <= 根号 n, 有一个出现了
// d 只要满足 <= n/d 即可
// 
// 不推荐:
//     试除法 : O(n^2) -> TLE
//    sqrt(n) : 每次调用函数导致很慢
//     i*i<=n : 当 n 接近于 int 的最大值时候(2147483647)
//              当 i^2 > n 的时候, 溢出就成负数

bool is_primeII(int n)
{
    if (n < 2) return false;            // 1 不是质数
    for (int i = 2; i <= n / i; ++ i )
        if (n % i == 0) return false;
    return true;
}

int main()
{
    // is_primeI();
    
    int m;
    scanf("%d", &m);
    
    while (m --)
    {
        int n;
        scanf("%d", &n);
        if (is_primeII(n)) printf("Yes\n");
        else printf("No\n");
    }
    
    return 0;
}
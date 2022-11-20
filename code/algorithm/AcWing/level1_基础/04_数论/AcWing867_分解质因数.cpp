#include <iostream>

using namespace std;

// 底数一定是质数, 枚举所有数会枚举到合数, 不会有问题
// 当枚举到 i 的时候已经把 2~i-1 的质因子都除完了, n 也在变化
// n 已经不包含任何 2~i-1 之间的质因子了
// n = 24
// 24/2 12 
// 12/2 6
// 6/2 3
// 所有质因子都出掉了, 就没有和 i 有关的质因子了
// 
// n 的范围
// n 中最多只包含一个 > sqrt(n) 的质因子
// 证明:
//      如果有两个 > sqrt(n) 相乘会 > n
// 因为只有一个 sqrt(n), 所以先将 < sqrt(n) 的质因子枚举出来
//
// 把跟一个数有关的 x^n 拿掉, 那么这个数和 x 有关的所有数, 就不存在倍数因数这个样的关系了
void divide(int n)
{
    // 从小到大枚举 n 的所有质因数, 如果 n % i == 0, 就把 i 的质数枚举出来
    // 分解质因数结果, 底数一定是质数
    
    for (int i = 2; i <= n / i; ++ i )
    {
        if (n % i == 0)                                                     
        {
            int s = 0;
            while ( n % i == 0)     // 当枚举到 i 的时候已经把 2~i-1 的质因子都除完了
                n /= i, ++ s;
            printf("%d %d\n", i , s);
        }
    }
    
    // 大于根号 n 的质因子, n 中最多只包含一个 > sqrt(n) 的质因子
    if (n > 1) printf("%d %d\n", n, 1);
    printf("\n");
}

int main()
{
    int n;
    scanf("%d", &n);
    
    while (n -- )
    {
        int x;
        scanf("%d", &x);
        divide(x);
    }
    
    return 0;
}
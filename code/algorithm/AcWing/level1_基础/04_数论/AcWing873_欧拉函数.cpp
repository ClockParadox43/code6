// φ(n) : 1~n 中与 n 互质数(gcd=1)的个数
// φ(6) = 1 2 3 4 5 6 
//        ^       ^ 
// 1和6互质
// 5和6互质
//
// 欧拉函数公式: 
// 假设 N 分解质因数后的结果是
// p1^α1 * p2^α2 * p3^α3..* pk^αk
// 公式 : φ(n) = N*(1-1/p1)*(1-1/p2)*(1-1/p3)...*(1-1/pk)
// ps: 如果要对一个数求欧拉函数的话要对其分解质因数
// 假设 N=6
// 6 = 2*3
// φ(6) = 6*(1-1/2)*(1-1/3) = 2 
//
// 时间复杂度:分解质因数的时间复杂度sqrt(n), 一共有 n 个数
//            所以时间复杂度是 n*sqrt(ai)
#include <iostream>

using namespace std;

int phi(int n)
{
    int res = n;
    
     // 分解质因数
    for (int i = 2; i <= n / i; ++ i )
        if (n % i == 0)
        {
            // res = res * (1 - 1 / i) 化简(不能有小数)
            res = res / i * (i - 1);
            while (n % i == 0) n /= i; 
        }
    
    if (n > 1) res = res / n * (n - 1);
    return res;
}

int main()
{
    int _ ;
    scanf("%d", &_ );
    while (_ -- )
    {
        int n;
        scanf("%d", &n);
        printf("%d\n", phi(n));
    }
    return 0;
}
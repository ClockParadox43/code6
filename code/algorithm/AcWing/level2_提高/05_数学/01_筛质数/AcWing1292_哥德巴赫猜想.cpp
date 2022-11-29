// 哥德巴赫猜想:
//      - 任意一个大于 4 的偶数都可以拆成两个奇数素数之和
//
//  8 = 3 + 5
// 20 = 3 + 17 = 7 + 13
// 42 = 5 + 37 = 11 + 31 = 12 + 29 = 19 + 23
//
// 验证所有小于一百万的偶数是否满足哥德巴赫的猜想, 如果有多组解输出差最大的
//
// 暴力:
// for (int a = 3; ; ++ a)  -> 0(N)
//      b = n - a;             
//      if (a && b 是质数) -> √n
// 时间复杂度:  O(n√n) => 10⁶ * √10⁶ = 10⁹
//
// 1) 1~10⁶ 的素数全部枚举出
//    for (a = all prime)  -> O(N)
//      b = n-a
//      if (st[b]) break; -> 打表判断 b 是否是质数 -> O(1)
//
//    质数定理:1~n 中质数个数是 n/lon, 最终时间复杂度为:O(n/lon + N)
//    10⁶ + T * 10⁶/log10⁶ 
//   = 10⁶ + T * 10⁶/20 
//   = 10⁶ + 50000T

#include <iostream>

using namespace std;

const int N = 1000010;

int primes[N], cnt;
bool st[N];

// 1) 预处理所有的质数(线性筛)
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

int main()
{
    init(N - 1);
    
    // 2) 枚举所有质数
    int n;
    while (cin >> n, n)     // 多组测试数据直到不是 0 为止
    {
        for (int i = 1; ; ++ i )    // 因为是要表示成两个数的奇素数之和, 因为一定解, 所以不需要考虑最大范围
        {
            int a = primes[i];
            int b = n - a;
            if (!st[b]) 
            {
                printf("%d = %d + %d\n", n, a, b);
                break;
            }  
        }
    }
    return 0;
}
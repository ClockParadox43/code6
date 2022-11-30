// 朴素解:
// 将所有数看做一个点, 质因子和其余数不能为同一组, 所以质数一组, 合数一组
// 连完后可发现是一个二分图
//
// 所以只要是质数就输出 1, 合数就输出 2 
#include <iostream>

using namespace std;

const int N = 100010;

int primes[N], cnt;
int st[N];

void init(int n)
{
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] * i <= n; ++ j )
        {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int main()
{
    int n; scanf("%d", &n);
    init(n + 1);        // 价值从 n + 1 开始

    if (n <= 2) puts("1");
    else puts("2");
    
    for (int i = 2; i <= n + 1; ++ i )
        if (!st[i]) printf("1 ");  // 合数输出 1 
        else printf("2 ");  // 素数输出 2
    return 0; 
}
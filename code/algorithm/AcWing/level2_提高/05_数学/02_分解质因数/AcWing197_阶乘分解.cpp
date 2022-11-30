// 给定一个 n 将 n! 解质因数
// N的范围:3≤N≤10^6 
// 因为 10^6! 很大, 所以 N 不可能先算出来, 会暴 int, 但是 该题答案很小, 因为 n! 中每个质因子小于等于 10^6
// 思路:先写出 n! 的表达式, 依次对 n! 的每个表达式因式分解, 然后对应的质因子相加
//          - 1 * 2 * 3 * 4 * 5
//      因为将 5! 所得结果和 120 的因式分解一样        
//      所以从 5! 的表达式中提取质因数进行分解, 乘法交换律, 只要数一样即可 
//      所以只要挑出它的质因数, 用 n 拿到该质因数的倍数(⌊n/p⌋ 直到除不进, 得到的也就是指数), 再累加上
//
//      调整顺序, 先枚举每个数的质因子
//      1) 筛出 1~10^6 中的所有质数 -> n/logn
//      2) 求 p 的次数
//          - 求 1~n 中 p 的倍数个数; ⌊n/p⌋ + ⌊n/p^2⌋ + ⌊n/p^3⌋ + ⌊n/p^4⌋ + .. + ⌊n/p^n⌋
#include <iostream>

using namespace std;

const int N = 1000010;

int primes[N], cnt;
bool st[N];

void init(int n)
{
    for (int i = 2; i <= n; ++ i )
    {
        if(!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] * i <= n; ++ j )
        {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int main()
{
    // 筛选出 1~n 中的所有质数
    int n; scanf("%d", &n);
    init(n);
    
    // 求一个数的指数个数, 
    for (int i = 0; i < cnt; ++ i )
    {
        int p = primes[i]; 
        int s = 0;
        for (int j = n; j; j /= p) s += j / p;  // 挑出所有和该质因子有关的倍数
        printf("%d %d\n", p, s);
    }    

    return 0;
}
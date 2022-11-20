#include <iostream>

using namespace std;

// 暴力 O(n^2) -> TLE
void get_primesI(int n)
{
    int cnt = 0;
    
    // 枚举每个 i 是否能被整除
    for (int i = 2; i <= n; ++ i )
    {
        int j = 2;
        for (j = 2; j < i; ++ j ) if (i % j == 0) break;
        if (i == j) cnt ++ ;
    }
    cout << cnt << endl;
}

const int N = 1000010;

int primes[N], cnt;
bool st[N];                 // 不能用状态压缩优化, 位数不够

// Eratosthenes 筛法利用的原理是 任意整数 x 的倍数 2x, 3x … 等都不是质数 .
// 但是即便如此也会有重复标记的现象, 例如12既会被2又会被3标记, 在标记2的倍数时, 12=6∗2
// 在标记3的倍数时, 12=4∗3, 根本原因是没有找到唯一产生12的方式
// 
//   2 3 4 5 6 7 8 9 10 11 12
//       x   x   x x x  p  x
//                    
// 1) 列出所有数 
// 2) 每次删除某个数的倍数
// 
// 这样筛完后, 所有数就只剩下质数
// 对于剩下的任何一个 p 数而言, 就说明 p 不是 2~p-1 中间任何一个数的倍数
// 反过来向, 2~n-1 之间任何一个数都不属于 p 的约数, 那么 p 就是质数
// 
// 时间复杂度: 每次枚举一个数 n/2, n/3, n/4 ... 也就是说调和级数大概和 lon 一个级别
// 朴素筛法: 将 for 循环放在 if 判断外面, 每个数都筛一次质数
// 埃氏筛法
// 优化:
//   并不需要把每个数的倍数全部删除, 只要删除质数的倍数即可 
//   因此可以把循环放到判断中去
//   只要知道 2~p-1 中的所有质数, 他只要不是 p 的约数的话, 那他就是一个质因数
//   所以去筛的时候只要把质数的倍数全部筛掉就可以了
//   当一个数不是质数的时候不需要删除它的所有倍数, 因为从小到大枚举, 那个数会被它的质数删掉
// 
// 时间复杂度:
//   比起优化前, 只要算质数的调和级数就可以了(n/2, n/3, n/5..)
// 
// 质数定理: 1~n 中 有 n/ln 个质数
// 
// 也就是说本来要算 ln 个数, 现在只要算 n/ln 个数
void get_primesII(int n)
{
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i])
        {
             primes[cnt ++ ] = i;
             for (int j = i + i; j <= n; j += i) st[j] = true;
        }
    }
}

// 线性筛
// 核心: 合数 n 只会被最小质因子 p[j] 筛掉
// 因为 j 从小到大枚举所有的质数, 只会把当前 p[j] 和 i 的乘积筛掉,  
void get_primesIII(int n)
{
    // 从小到大筛每个数, i 可以作为最大因数
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i]) primes[cnt ++ ] = i;        
        for (int j = 0; primes[j] <= n / i; ++ j )  // primes[j] <= n/i: 变形一下得到 primes[j]*i <= n, 把大于 n 的合数都筛了就 没啥意义了
        {
            // 标记 primes[j]一定是 primes[j]*i 的最小质因子
            st[primes[j] * i] = true;

            // 表明 primes[j] 一定是 i 的最小质因子, 没有必要再遍历, primes要小于等于 i 的最小质因子
            // 这样能保证每个数遍历一遍, 而没有重复  
            if (i % primes[j] == 0) break;      
        }
    }
}
//  当 i%primes[j]!=0 时, 说明此时遍历到的 primes[j] 不是i的质因子, 那么只可能是此时的 primes[j]<i 的
//  最小质因子, 所以 primes[j]*i 的最小质因子就是primes[j];

int main()
{
    int n;
    scanf("%d", &n);
    get_primes(n);
    printf("%d\n", cnt);
    
    for (int i = 0; i < cnt; ++ i ) printf("%d ", primes[i]);
    return 0;
}

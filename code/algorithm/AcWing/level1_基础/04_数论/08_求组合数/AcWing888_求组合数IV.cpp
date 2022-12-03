// 先把 Cab 分解质因数, 这样就可以将它变成一个只有乘法的形式(分解质因数后再计算 a!), 这样之后只需要实现一个高精度乘法即可
// 如何求一个阶乘当中包含多少个因子 p : a! = ⌊a/p⌋ + ⌊a/p²⌋ + ⌊a/p³⌋ ... (直到 p^n > a)
// ⌊a/p⌋ 表示: 1~a 当中 p 的倍数的个数 
//                         
// 1) 先预处理出所有质因子, 求出质因子的次数是多少
// 2) 先看一下分子中的 p 的个数, 再将分母中 p 的个数减去 (差值就是 p 的个数)

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 5010;

int primes[N], cnt;
int sum[N];     // 记录每个质数的次数
bool st[N];

void get_primes(int n)
{
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; ++ j )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

// 对 p 的各个小于等于 a 的次数向下取整倍数
int get(int n, int p)
{
    // 求 n! 中 p 的个数
    int res = 0;
    while (n) 
    {
        res += n / p;
        n /= p; 
    }
    return res;
}

vector<int> mul(vector<int> &A, int b)
{
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); ++ i )
    {
        t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }

    while (t)
    {
        C.push_back(t % 10);
        t /= 10;
    }
    // while(C.size()>1 && C.back()==0) C.pop_back();//考虑b==0时才有pop多余的0 b!=0不需要这行
    return C;
}

int main()
{
    int a, b; scanf("%d%d", &a, &b);
    get_primes(a);
    
    // 求每个质数的次数
    // 
    for (int i = 0; i < cnt; ++ i )
    {
        int p = primes[i];
        sum[i] = get(a, p) - get(a - b, p) - get(b, p);     // 求出当前这个数中包含的 p 的次数是多少
    }                                                       // 数据范围: 1≤b≤a≤5000, a 是大于 b 的, 所以只需要求 a 就可以了, 这样b, a−b 都出来了

    vector<int> res;
    res.push_back(1);

    for (int i = 0; i < cnt; ++ i )
        for (int j = 0; j < sum[i]; ++ j )
            res = mul(res, primes[i]);

    for (int i = res.size() - 1; i >= 0; -- i ) printf("%d", res[i]);
    puts("");
    
    return 0;
}
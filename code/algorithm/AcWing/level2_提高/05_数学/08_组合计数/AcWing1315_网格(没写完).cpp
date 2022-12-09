#include <iostream>

using namespace std;

const int N = 100010;

int primes[N], cnt;
int st[N];
int a[N], b[N]; // C(m+n, n) 结果存储在 a 中, C(m+n, m-1) 结果存储在 b 中

// 筛质数
void init(int n)
{
    for (int i = 2; i <= n; ++ i )
    {
        if (!st[i]) primes[cnt ++ ];
        for(int j = 0; primes[j] * i <= n; ++ j )
        {
            st[primes[j] * i] = true;
            if (i % primes[j]== 0) break; 
        }
    }
}

// 返回 n 中质因数 p 的个数
int get(int n, int p)
{
    int s = 0;
    while (n) s += n / p, n /= p;
    return s;
}

// 返回组合数C(x, y)，结果存储在r中, r[0]是最低位
int C(int x, int y, int r[])
{
    int len =  1;
    r[0] = 1;

    for (int i = 0; i < cnt; ++ i )
    {
        int p = primes[i];
        int s = get(x, p) - get(y, p) - get(x - y, p);
        while (s -- ) mul(r, len, p);
    }
    return len;
}

// 高精度减法
void sub(int a[], int al, int b[], int bl)
{ 
    for (int i = 0, t = 0; i < al; ++ i )
    {
        a[i] -= t + b[i];
        if (a[i] < 0) a[i] += 10, t = 1;
        else t = 0;
    }
}

int main()
{
    init(N - 1);        // 筛质数

    int n, m; scanf("%d%d", &n, &m);

    // 求出 C(m+n, n) 结果存储在 a 中, C(m+n, m-1) 结果存储在 b 中
    int al = C(n + m, m, a);        // al 是数据 a 的长度
    int bl = C(n + m, m - 1, n);    // bl 是数据 b 的长度
    
    // C(m+n, n) - C(m+n, m-1): 结果存储在 a 中
    sub(a, al, b, bl);

    int k = al - 1;
    while (!a[k]) -- k;
    while (k >= 0) printf("%d", a[k -- ]);

    return 0;
}
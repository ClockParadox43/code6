// 给定三个整数 N,L,R, 统计长度在 1 到 N 之间, 元素大小都在 L 到 R 之间的单调不降序列的数量
// 输出答案对 106+3 取模的结果
//      - 数据加工后才能使用隔板法, 直接减会导致减去球的个数
// 详细过程看截图
// 最后代码用 lucas 定理答案:
//      - C(R-L+n+1, R-L+1)
#include <iostream>

using namespace std;

typedef long long LL;

const int p = 1000003;

int qmi(int a, int k)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

int C(int a, int b)
{
    if (a < b) return 0;
    
    int down = 1, up = 1;
    for (int i = a, j = 1; j <= b; -- i, ++ j )
    {
        up = (LL)up * i % p;
        down = (LL)down * j % p;
    }
    return (LL)up * qmi(down, p - 2) % p;
}

int lucas(int a, int b)
{
    if (a < p && b < p) return C(a, b);
    return (LL)lucas(a / p, b / p) * C(a % p, b % p) % p;
}

int main()
{
    int q; scanf("%d", &q);
    while (q -- )
    {
        int n, l, r; scanf("%d%d%d", &n, &l, &r);
        cout << (lucas(r - l + n + 1, r - l + 1) + p - 1) % p << endl;
    }
    return 0;
}
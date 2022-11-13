#include <iostream>

using namespace std;

const int N = 100010;

int n, m, x;
int a[N], b[N];

// 对于每一个 i 找一个 j, 使得 a[i] + b[j] <= x
// 因为 sum 是不变的当 i 变大时, j 变小

int main()
{
    scanf("%d%d%d", &n, &m, &x);
    for (int i = 0; i < n; ++ i ) scanf("%d", &a[i]);
    for (int i = 0; i < m; ++ i ) scanf("%d", &b[i]);

    for (int i = 0, j = m - 1; i < n; ++ i )
    {
        while (j >= 0 && a[i] + b[j] > x) -- j;         // ≤ 时退出循环
        if (a[i] + b[i] == x)
        {
            printf("%d %d\n", i, j);
            break;
        }
    }

    return 0;
}
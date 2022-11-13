#include <iostream>

using namespace std;

const int N = 100010;

// DP 也可以做
// 双指针也可以做
int n, m;
int a[N], b[N];

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; ++ i ) scanf("%d", &a[i]);
    for (int i = 0; i < m; ++ j ) scanf("%d", &b[i]);

    int i = 0, j = 0;
    while (i < n && j < m)
    {
        if (a[i] == b[j]) ++ i;
        ++ j;
    }

    i == n ? printf("Yes\n") : printf("No\n");
    return 0;
}
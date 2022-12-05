#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;

const int N = 4;

int n, m;

void mul(int c[][N], int a[][N], int b[][N])    // c = a * b
{
    static int t[N][N]; // 防止反复开辟空间
    memset(t, 0, sizeof t);

    for (int i = 0; i < N; ++ i )
        for (int j = 0; j < N; ++ j )
            for (int k = 0; k < N; ++ k )
                t[i][j] = (t[i][j] + (LL)a[i][k] * b[k][j]) % m;
    memcpy(c, t, sizeof t);
}

int main()
{
    scanf("%d%d", &n, &m);
    int f1[N][N] = {1, 1, 1, 0};
    int a[N][N] = {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 1},
    };

    int k = n - 1;

    // 快速幂
    while (k)
    {
        if (k & 1) mul(f1, f1, a);  // f1 = f1 * a
        mul(a, a, a);   // a = a * a
        k >>= 1;
    }

    cout << (((LL)n * f1[0][2] - f1[0][3]) % m + m) % m << endl;
    return 0;
}
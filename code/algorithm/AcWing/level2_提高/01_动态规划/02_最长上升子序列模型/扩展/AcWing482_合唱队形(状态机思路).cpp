#include <iostream>

using namespace std;

const int MAXN = 110;

int n;
int w[MAXN];
int f[MAXN][2];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) scanf("%d", &w[i]);

    for (int i = 1; i <= n; ++ i)
    {
        f[i][0] = f[i][1] = 1;
        for (int j = 1; j < i; ++ j)
        {
            if (w[i] > w[j]) f[i][0] = max(f[i][0], f[j][0] + 1);
            if (w[i] < w[j]) f[i][1] = max(f[i][1], max(f[j][0], f[j][1]) + 1);
        }
    }

    int res = 0;
    for (int i = 1; i <= n; ++ i) 
        res = max(res, max(f[i][0], f[i][1]));
    printf("%d", n - res);
    return 0;
}
#include <iostream>

using namespace std;

const int MAXN = 103;

int T, n;
int w[MAXN];
int f[MAXN], fl[MAXN];

int main()
{
    scanf("%d", &T);
    while (T -- )
    {
        int ans = 0; scanf("%d", &n);
        for (int i = 1; i <= n; ++ i) scanf("%d", &w[i]);
        for (int i = 1; i <= n; ++ i)
        {
            f[i] = fl[i] = 1;
            for (int j = 1; j < i; ++ j)
                if (w[i] < w[j]) f[i] = max(f[i], f[j] + 1);   // 后面的小于前面的, 求的是最长下降子序列
                else fl[i] = max(fl[i], fl[j] + 1);            // (a[i] > a[j]) 后面的大于前面的, 求的是最长上升子序列
            ans = max(ans, max(f[i], fl[i]));
        } 
        printf("%d\n", ans);
    }
    return 0;
}
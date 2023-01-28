#include <iostream>

using namespace std;

const int MAXN = 1003;

int n;
int w[MAXN];
int f[MAXN], fl[MAXN];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) scanf("%d", &w[i]);

    // 求最长上升子序列    
    for (int i = 0; i < n; ++ i)
    {
        f[i] = 1;
        for (int j = 0; j < i; ++ j)
            if (w[i] > w[j]) f[i] = max(f[i], f[j] + 1);
    }
    
    // 求最长下降子序列  
    for (int i = n - 1; i >= 0; -- i)
    {
        fl[i] = 1;
        for (int j = n - 1; j > i; -- j)    
            if (w[i] > w[j]) fl[i] = max(fl[i], fl[j] + 1);
    }

    // 以 w[i] 结尾的最长上升子序列 + 以 w[i] 结尾的最长下降子序列 - 峰顶
    int ans = 0;
    for (int i = 0; i < n; ++ i)
        ans = max(ans, f[i] + fl[i] - 1);
    
    printf("%d", ans);
    return 0;
}
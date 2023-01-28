// 状态表示 f[i]
//     - 集合: 所有 a[i] 结尾的上升子序列
//     - 属性: 和的最大值
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1010;

int n;
int w[MAXN], f[MAXN];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) scanf("%d", &w[i]);

    int res = 0;
    for (int i = 0; i < n; ++ i)
    {
        f[i] = w[i];
        for (int  j = 0; j < i; ++ j)
            if (w[i] > w[j])    
                f[i] = max(f[i], f[j] + w[i]);
        res = max(res, f[i]);
    }
    
    printf("%d\n", res);
    return 0;
}
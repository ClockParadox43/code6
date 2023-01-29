//                集合: 所有第一个序列的前 i 个字母, 和第二个序列的前 j 个字母构成的 
//              /       且以 b[j] 结尾的公共上升子序列
//      状态表示
//   /          \ 
// DP             属性: Max
//   \  
//     状态计算  f[i,j]
//                                   |                    
//          _________________________|________
//         |    |    |    |   |      |        | -> 所有不包含  
//         |null|b[1]|b[2]|...|b[j-1]|f[i-1,j]|    a[i] 的公共上升子序列
//         |____|____|____|___|______|________|
//                |                  |
//                v                  |
//            所有包含 a[i]           
//            的公共上升子序列       


#include <iostream>
#include <algorithm>

using namespace std;

const int N = 3010;

int n;
int a[N], b[N];
int f[N][N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            f[i][j] = f[i - 1][j];              // 没有包含 a[i] 的情况
            if (a[i] == b[j])                   // 包含了 a[i] 相等
            {
                f[i][j] = max(f[i][j], 1);      // 固定了 a[i] 后, 求以 b[j] 结尾的最长上升子序列 
                for (int k = 1; k < j; ++k)
                    if (b[k] < a[i])
                        f[i][j] = max(f[i][j], f[i][k] + 1); // f[i][k] : j~k 的序列
            }                                                // f[i][j] : 以 b[j] 结尾可以作为候选的序列
        }

    int res = 0;
    for (int i = 1; i <= n; ++i) res = max(res, f[n][i]);

    printf("%d\n", res);
    return 0;
}
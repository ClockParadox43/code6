// 给定两个长度分别为 N 和 M 的字符串 A 和 B, 求既是 A 的子序列又是 B 的子序列的字符串长度最长是多少
// 数据范围:
// 1 ≤ N,M ≤ 1000
// 
// 状态表示:所在第 1 个序列的前 i 个字母中出现, 且在第 2 个序列的前 j 的子序列
//     属性:max
//     集合:划分为 4 种情况
//          1) ai, bj都不选
//          2) ai, bj都选
//          3) 选 ai 不选 bj
//          4) 不选 ai, 选 bj
// 状态计算:f[i-1,j-1], f[i+1,j+1], f[i,j-1], f[i-1,j]
//              00          11         10        01  
//      f[i-1,j-1]:不选 a[i] 不选b[j] 等价于在第一个序列中的前 i-1 个子母中出现
//                 并且在第二个序列中的前 j-1 个字母中出现, 的子序列最大值
// 
//      f[i,j]: 的最大值是这 4 种情况取 max
//      
//      f[i-1,j]:
//          f[i-1,j] 要表示的是所有在第一个序列的前 i-1 个字母中出现, 且在第二个序列的前 j 个字母中出现的子序列.
//          01 想表示的是 ai 不出现在子序列中, bj 一定出现在子序列中的情况
//          b[j] 表示的是子序列在 b 的前 j 个字母中出现但是不一定包含最后一个字母
//          f[i-1,j] 在该种表达中不一定包含 b
//          b 在第二个序列的前 j 个字母中出现但是不一定包含最后一个字母
//
//      4 种情况中存在重叠
//      f[i-1,j] 包含了 01 这个情况 和 f[i-1, j-1] 这种情况, f[i-1,j] 被 f[i,j] 包含
//      如果不求最大值, 这种情况一样会被更新
// 
//      f[i-1, j] 和 f[i, j-1] 都包含 f[i-1, j-1] 这种情况, 但是取 max 的时候实际还是取他们三者的最大值, 所以可以重复
//  时间复杂度:O(n^2)
//
// 值得注意的是因为 f[i][j] 求的是最好长度, 所以会与 f[i][j-1], f[i-1][j] 要当前字符
// 或者不要当前字符的含义不相符, 表中优先存最好值, 每次都会找最大的然后推到最后面
// 想不起来就调试去
// 
// 2023.1.25 更新: 这不废话嘛, 本来求的就是 max, 你以前理解错了
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
char a[N], b[N];
int f[N][N];

int main()
{
    scanf("%d%d", &n, &m);
    scanf("%d%d", a+1, b+1);    // 涉及到 i-1, 下标从 1 开始
    
    for (int i = 1; i <= n; ++ i ) cin >> a[i];
    for (int i = 1; i <= m; ++ i ) cin >> b[i];
    
    // 固定住 i 去枚举 j 
    for (int i = 1; i <= n; ++ i )
        for (int j = 1; j <= m; ++ j ) 
        {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if (a[i] == b[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }
    printf("%d", f[n][m]);
    return 0;
}   

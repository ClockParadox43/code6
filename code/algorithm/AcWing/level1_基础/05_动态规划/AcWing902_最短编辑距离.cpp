// 给定两个字符串 A 和 B, 现在要将 A 经过若干操作变为 B, 可进行的操作有:
// 
// 删除–将字符串 A 中的某个字符删除
// 插入–在字符串 A 的某个位置插入某个字符
// 替换–将字符串 A 中的某个字符替换为另一个字符
// 现在请你求出, 将 A 变为 B 至少需要进行多少次操作
// 数据范围
// 1 ≤ n, m ≤ 1000
//
// 状态表示: 所有 a[1~i] 变成 b[1~j] 的操作方式
//     属性: Min
//     集合: 求 ai, bi 已经相等的情况下, 最短的操作方式
// 状态计算:
//     删除: f[i-1,j] -> a[i-1]和b[j]位置都相等了 
//       增: f[i,j-1] -> a[i]和b[j-1]位置都相等了                   
//       改: f[i-1,j-1] -> a[i-1]和b[j-1] 位置都相等了
// 时间复杂度: O(n^2) 
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
char a[N], b[N];
int f[N][N];

int main()
{
    scanf("%d%s", &n, a + 1);
    scanf("%d%s", &m, b + 1);

    // f[0][i]如果a初始长度就是0，那么只能用插入操作让它变成b
    // f[i][0]同样地，如果b的长度是0，那么a只能用删除操作让它变成b
    // 
    // 需要操作的次数和 a, b 的长度是有关系的
    // 有 i 个字母就需要 i 步
    for (int i = 0; i <= m; ++ i ) f[0][i] = i;
    for (int i = 0; i <= n; ++ i ) f[i][0] = i;

    for (int i = 1; i <= n; ++ i )
        for (int j = 1; j <= m; ++ j )
        {
            f[i][j] = min(f[i - 1][j] + 1, f[i][j - 1] + 1);
            if (a[i] == b[j]) f[i][j] = min(f[i][j], f[i - 1][j - 1]);  // 相等就不用修改
            else f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
        }
    
    printf("%d", f[n][m]);

    return 0;
}
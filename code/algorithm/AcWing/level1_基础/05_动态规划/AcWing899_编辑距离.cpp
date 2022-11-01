// 最短编辑距离的应用题:求若干次最短编辑距离

#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

const int N = 15, M = 1010;

int n, m;
int f[N][N];
char str[M][M];

// 将 b 修改成 a
int edit_distance(char* a, char* b)
{
    int la = strlen(a + 1), lb = strlen(b + 1);

    // 如果 a 字符串有 i 个, 那么 b 需要删除 i 次才能变成 a 字符串, 删除和 b 长度有关
    // 如果 a 字符串有 i 个, 那么 b 需要增加 i 次才能变成 a 字符串, 增加和 a 长度有关
    for (int i = 0; i <= lb; ++ i ) f[0][i] = i;
    for (int i = 0; i <= la; ++ i ) f[i][0] = i;

    for (int i = 1; i <= la; ++ i )
        for (int j = 1; j <= lb; ++ j )
        {
            f[i][j] = min(f[i - 1][j] + 1, f[i][j - 1] + 1);
            f[i][j] = min(f[i][j], f[i - 1][j - 1] + (a[i] != b[j]));
        }

    return f[la][lb];
}

int main()
{
    // 输入 n 个长度为 n 的字符串
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i ) scanf("%s", str[i] + 1);

    while (m -- )
    {
        char s[N];
        int limit;
        scanf("%s%d", s + 1, &limit);   // 输入要查询的字符串和限制

        // 样本字符串和当前要查询的字符串做对比
        int res = 0;
        for (int i = 0; i < n; ++ i )
            if (edit_distance(str[i], s) <= limit)
                ++res;
        printf("%d\n", res);
    }

    return 0;
}

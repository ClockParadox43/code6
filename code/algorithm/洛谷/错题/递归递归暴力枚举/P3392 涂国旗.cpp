#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;
const int MAXN = 54;

int n, m;
char w[MAXN][MAXN];
int ans, sum = 1e5;

// 每种颜色的状态都在变化

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; ++i) scanf("%s", w[i] + 1);

    // 从第 i 行枚举到第 j 行
    // 循环内部, k(i~j) 的范围枚举每个格子g 
    for (int i = 1; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)    // 终点行, 剩下的都是 R 的范围, R 最后一行需要看所以是 < n 
        {
            int ans = 0; // 记录范围内总的代价, 枚举每个颜色需要枚举的不同的范围

            for (int k = 1; k <= i; ++k)       // k <= i, 白色在最上面, 枚举到 i, 蓝色 i+1 开始
                for (int g = 1; g <= m; ++g)   // 枚举该行的颜色
                    if (w[k][g] != 'W') ++ans;

            for (int k = i + 1; k <= j; ++k)    // 蓝色从第 i+1 行(红色下面开始)枚举到第 j 行
                for (int g = 1; g <= m; ++g)
                    if (w[k][g] != 'B') ++ans;

            for (int k = j + 1; k <= n; ++k)    // 红色是剩下的一行, 从蓝色下面开始, j + 1 到最后一行 n
                for (int g = 1; g <= m; ++g)
                    if (w[k][g] != 'R') ++ans;

            sum = min(sum, ans);
        }

    cout << sum << endl;
    return 0;
}
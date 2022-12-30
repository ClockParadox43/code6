// 教练准别 3 套模拟题, 在接下来的 5 天中, 有 3 天有空比赛
// 
// 接下来的 1 行, 每行 3 个数据, 
// 1 行 1 列的整数 a[i, j] 表示第 1 人在接下来的 5 天中第 1 个有空日子为 a[i,j] = 2
//
// 1 3 5
// 2 3 5
// 
// 1 2 3 4 5
// 0 1 1 0 1

#include <iostream>

using namespace std;

const int N = 1010;

int q[N][N];

int main()
{
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            int x; scanf("%d", &x);
            q[i][j] = x;
        }
    }

    // 如果不同的人(行不同)他们第 j 个有空日子都是 q[i, j], 那么 cnt 不用加 1, 用同一套卷子即可
    // 如果不同的人(行不同)他们的第 j 个有空日子不同但 q[i, j] 相同, cnt 加一

    // 第一天, 枚举有空日子都是 1 的, 如果列也就是 j 不一样就加一

    for (int x = 1; x <= k; ++x)        // 第一重循环, 统计都是第 x 天的人
    {
        int cnt = 0;
        int flag = 0;       // 记录做不同套卷子的人
        for (int i = 1; i <= m; ++i)     // 第二重循环枚举的是列, 做第 i 套卷子 
        {
            for (int j = 1; j <= n; ++j) // 第三重循环枚举的是行, 第 j 个人
                if (q[j][i] == x)       // 如果 第 i 个人第 j 个日子有空的日子在 x
                {
                    if (flag == 0)      // 枚举到第一个人情况的时候
                    {
                        cnt++;
                        flag = i;
                    }

                    // flag != i 说明不是同一套卷子了
                    if (flag && flag != i)
                    {
                        cnt++;
                        flag = i;
                    }
                }
        }
        cout << cnt << ' ';
    }

    return 0;
}
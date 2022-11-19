// 染色法
// 将所有点分成两个集合, 使得所有边只出现在集合之间, 就是二分图
// 二分图: 一定不含有奇数环, 可能包含长度为偶数的环, 不一定是连通图
// 
// dfs版本
// 代码思路:
// 染色可以使用 1 和 2 区分不同颜色, 用 0 表示未染色
// 遍历所有点, 每次将未染色的点进行 dfs, 默认染成 1 或者 2
// 由于某个点染色成功不代表整个图就是二分图, 因此只有某个点染色失败才能立刻 break/return
// 染色失败相当于存在相邻的 2 个点染了相同的颜色
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 1e5 + 10, M = 2e5 + 10;   // 由于是无向图, 顶点数最大是N，那么边数M最大是顶点数的2倍
int e[M], ne[M], h[N], idx;
int st[N];


void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool dfs(int u, int color)
{
    st[u] = color;
    for (int i = h[u]; i != -1; i = ne[i] )
    {
        int j = e[i];
        if (!st[j])  // 没有染色过就去深度优先遍历
            if (!dfs(j, 3 - color)) return false;       
        else if (st[j] == color) return false;          // 相邻的边同一种颜色
    }
    return true;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    
    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }

    // 遍历所有点, 每次将未染色的点进行 dfs, 默认染成 1 或者 2
    // 如果是一棵树 DFS 可以全部染完, 图就不一定了
    bool flag = true;
    for (int i = 1; i <= n; ++ i )      // 枚举所有点
    {
        if (!st[i])                
        {
            if (!dfs(i, 1))         // 染色失败相当于存在相邻的2个点染了相同的颜色
            {
                flag = false;
                break;
            }
        }
    }

    if (flag) puts("Yes");
    else puts("No");
    return 0;
}
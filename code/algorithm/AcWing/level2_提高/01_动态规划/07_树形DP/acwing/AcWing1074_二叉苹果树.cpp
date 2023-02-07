// 每个点都会依赖自己的父节点才会被保留, 可以想到有依赖的背包问题
// f[i,j]:在以i为根的子树中选择j条边的最大价值
//          对于父节点的每个子节点, 可以将子节点看做是分组背包中的一组物品 
#include <iostream>

using namespace std;


/*
该题区别于[有依赖的背包问题](https://www.acwing.com/problem/content/10/)的唯一一个不同点:
之前为点权, 现在为边权
有依赖的背包问题: 因为是点权, 所以可以枚举完所有的分组, 最后加上这个点的权值
该题: 因为是边权, 所以不能最后再加上边权
f(i)(j)(k):以i为根的所有子树, 从前j个子树中选, 保留恰好k条边的集合
属性：max
状态划分: 第j个子树选和不选
1.第j个子树内不选, f(i)(j - 1)(k - 1) + f(son)(子树中的子树的大小)(0)+ w[i]  (画图可知)
2.第j个子树选--> 选t个 (t >= 0 && t <= k - 1)  f(i)(j - 1)(k - t - 1) + f(son)(子树中子树的大小)(t) + w[i]
从j个子树中选, 恰好对应for(int i = h[sta] ; ....)
且考虑到方程转移, 仅仅和j - 1 有关, 可以滚动数组优化, 倒序枚举V
初始化问题: 因为是恰好k条边的集合且属性为MAX, 把全体状态初始化为-INF, 每个节点f(i)(0) = 0 
且要考虑边界问题, 有些子树无法取到K条边
*/
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110, M = N << 1;

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int f[N][N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

// 先阶段, 再状态, 再决策
void dfs(int u, int father)
{
    // 枚举所有物品组
    for (int i = h[u]; ~ i; i = ne[i])
    {
        int ver = e[i];
        if (ver == father) continue;
        dfs(ver, u);
        for (int j = m; j >= 0; -- j)
            for (int k = 0; k <= j - 1; ++ k) // 枚举体积预留一条连向父节点的边, 决策每组选择哪个物品
            // f[ver][k]:该组的价值
            // w[i]:自己的边
            // 以体积为单位分组
                f[u][j] = max(f[u][j], f[u][j - k - 1] + f[ver][k] + w[i]);
    }
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; ++ i)
    {
        int a, b, c; cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    dfs(1, -1);
    cout << f[1][m] << endl;
    return 0;
}
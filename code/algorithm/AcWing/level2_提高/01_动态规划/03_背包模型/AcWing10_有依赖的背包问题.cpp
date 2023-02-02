// 在满足依赖关系的情况下最多可以选择的物品价值
// 如果我们想选择某一棵子树, 那就必须选择这棵子树的根节点
// 因此我们采用递归的思路来考虑
//
// 
// 思路: 在不同的体积下, 求出f[u,j]的最大价值是多少
// 目标: 求出以u为根的子树, 在不同的体积下, 他的最大价值是多少
// 状态表示f[u,j]:所有从以u为根的子树中选, 且总体积不超过j的方案
#include <iostream>
#include <cstring>

using namespace std;

const int N = 110;
int n, m;
int v[N], w[N];
int h[N], e[N], ne[N], idx;
int f[N][N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u)
{
    // 先枚举所有状态体积小于等于j-v[u]的所有子节点们能够获得的最大价值
    for (int i = h[u]; ~ i; i = ne[i])  // 循环物品组
    {
        int t = e[i];
        dfs(t); // 从下往上算, 先计算子节点的状态
        
        // 对u的所有子树做分组背包, 枚举所有要被更新的状态
        // 因为u是该树的根节点, 所以必选, 预留出u的空间
        for (int j = m - v[u]; j >= 0; -- j) 
            for (int k = 0; k <= j; ++ k)
            // 循环决策, 枚举该子节点在体积j下能使用的所有可能体积数 
            // j - k:为孩子的体积腾出空间
                f[u][j] = max(f[u][j], f[u][j - k] + f[t][k]);
    }
    // 最后选择第u件物品
    for (int j = m; j >= v[u]; -- j) f[u][j] = f[u][j - v[u]] + w[u];
    for (int j = 0; j < v[u]; ++ j) f[u][j] = 0;        // 清空没有悬赏u的所有状态
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    int root;
    for (int i = 1; i <= n; ++ i)
    {
        int p; cin >> v[i] >> w[i] >> p;    // 体积, 价值, 所依赖的物品编号
        if (p == -1) root = i;
        else add(p, i);
    }

    dfs(root);
    cout << f[root][m] << endl;
}
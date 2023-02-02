#include <iostream>
#include <cstring>

using namespace std;

const int N = 110;
int n, m;
int v[N], w[N];
int h[N], e[N], ne[N], idx;
int f[N][N]; // f[x][v]表达选择以x为子树的物品, 在容量不超过v时所获得的最大价值

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u)
{
    //点x必须选, 所以初始化f[u][v[u] ~ m]= w[u]
    // 先储存u体积为i的时候, 对应的u的价值w
    for(int i = v[u]; i <= m; ++ i)
        f[u][i] = w[u];
    
    // 枚举所有物品
    for(int i = h[u]; ~ i ;i = ne[i])
    {
        int son = e[i];
        dfs(son);
        // 此时自己孩子的决策已经分配好了

        // 因为u是该树的根节点, 所以必选, 预留出u的空间
        for(int j = m; j >= v[u]; j -- )  
            for(int k = 0; k <= j - v[u]; k ++ ) // 循环决策, 枚举该子节点在体积j下能使用的所有可能体积数
                f[u][j] = max(f[u][j], f[u][j - k] + f[son][k]);
    }
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
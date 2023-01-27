// 树形DP, 要弄清楚是用子节点的信息更新父亲节点, 还是根据父亲节点的信息更新子节点的信息
// 状态表示: 
//      f[u][0]:所有以 u 为根的子树中选, 不选择以 u 为当前节点的方案
//      f[u][0]:所有以 u 为根的子树中选, 选择以 u 当前节点的方案
// 状态计算:
//      f[u][0] ∑ max(f[s][0], f[s][1])
//      不选择当前 u 的情况下, 选择以子树为根节点 和 不选择以子树为根节点的求最大值      
//      f[u][1] ∑ f[s][0]
//      上司选了, 子树就不能选
//
// 一共有 2n 种状态, 但是每个状态算的时候是他的儿子的数量
// 时间复杂度 O(n-1)
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 6010;

int n;
int happy[N];
int h[N], e[N], ne[N], idx;
int f[N][2];
// f[u][1]:以u为根节点的子树并且包括u的最大快乐指数
// f[u][0]:以u为根节点并且不包括u的最大快乐指数
bool has_father[N];

// a 有通往 b 的路径
void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

// 深度优先遍历自己的 child
void dfs(int u)
{
    f[u][1] = happy[u]; // 如果选择加上当前快乐值

    // 遍历自己的所有孩子, 节点有 n 个, 所以 f 不会越界, 越界的 ne[i] = -1;
    // f[] 和 h[] 映射关系, i 由 idx(全局) 记录, 所以第一无二
    for (int i = h[u]; i != -1; i = ne[i] )
    {
        int j = e[i];
        dfs(j);
        f[u][0] += max(f[j][0], f[j][1]);
        f[u][1] += f[j][0];
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i ) scanf("%d", &happy[i]);

    // 节点之间的关系用邻接表记录, 输入 n-1 条边(有 n 个点就有 n-1 条边)
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; ++ i ) 
    {
        // b 是 a 的直接上司, b 有一条指向 a 的边
        int a, b;
        scanf("%d%d", &a, &b);
        has_father[a] = true;
        add(b, a); 
    }

    int root = 1;
    while (has_father[root]) ++ root;   // 找到没有上司的节点
    dfs(root);

    printf("%d", max(f[root][0], f[root][1]));  // 判断两种方案(最大的上司到底要不要来)
    return 0;
}
// 往上走的最远和往下走的最远取一个max, 就是树的中点
// 三个数组向下走的最大值次大值, 向上走的最大值(因为是从下往上返回的, 此时上面的节点还没有更新过)
// 思路:两遍dfs, 用子节点去更新父节点的信息
//               用父节点去更新子节点的信息, 需要分成两种情况来对待
//                  1.向上走
//                  2.向下走, 如果经过当前点就返回次大值(不重复计算)
//                            如果不经过当前点返回最大值

// ps: 只有当节点不是叶子节点时, 才存在向下走的路径.
///    同理只有当节点不是根节点时, 才存在向上走的路径.
//     所以最后在求最小值时, 如果是叶节点, 则只能用up[i]更新, 如果是根节点, 则只能用d1[u]更新
#include <iostream>
#include <cstring>

using namespace std;

const int N = 10010, M = 2 * N, INF = 0x3f3f3f3f;

int n;
int h[N], e[M], w[M], ne[M], idx;
int d1[N], d2[N], p1[N], up[N];
int is_leaf[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int dfs_d(int u, int father)
{
    d1[u] = d2[u] = -INF;
    for (int i = h[u]; ~ i; i = ne[i])
    {
        int t = e[i];
        if (t == father) continue;
        int d = dfs_d(t, u) + w[i];
        if (d >= d1[u]) 
        {
            d2[u] = d1[u], d1[u] = d;
            p1[u] = t;  // 表示当前被更新的u这个父节点的下一个点为t
        }
        else if (d > d2[u]) d2[u] = d;
    }
    if (d1[u] == -INF)  // 如果没有被更新说明是叶节点, 那么最大值和次大值都是0, 而且标记为叶节点
    {
        d1[u] = d2[u] = 0;
        is_leaf[u] = true;
    }
    return d1[u];       // 每次返回这个最大值
}

void dfs_u(int u, int father)   // 第一步向上递归, 对二步向下或继续向上递归的过程
{
    for (int i = h[u]; ~ i; i = ne[i])
    {
        int t = e[i];
        if (t == father) continue;  
        // p1[u] == t: 说明遇到了之前向下递归的那条路径, 为了避免路径重复
        // 那么只能用次大值来更新这条路径的长度
        if (p1[u] == t) up[t] = max(up[u], d2[u]) + w[i];
        else up[t] = max(up[u], d1[u] + w[i]);
        // 从t这个点的向上路径的长度等于它父节点u继续
        // 向上到其他点的路径或父节点向下的路径的长度加u和t直接的距离
        dfs_u(t, u);
    }
}

int main()
{
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; ++ i)
    {
        int a, b, c; cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    dfs_d(1, -1);   // down
    dfs_u(1, -1);   // up
    int res = d1[1];
    for (int i = 2; i <= n; ++ i)
        if (is_leaf[i]) res = min(res, up[i]);
        else res = min(res, max(d1[i], up[i]));
    cout << res << endl;
    return 0;
}
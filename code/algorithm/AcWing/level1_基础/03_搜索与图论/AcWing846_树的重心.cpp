// 深度优先遍历的好处可以每次算出子树的大小
// 重心定义: 重心是指树中的一个结点, 如果将这个点删除后, 
//           剩余各个连通块中点数的最大值最小, 那么这个节点被称为树的重心
#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010, M = N * 2;

// h[]: 存储 N 个链表的链表头
// e[]: 存储每个值
// ne[]: 存储每个节点的 next 指针
int n;
int h[N], e[M], ne[M], idx;
bool st[N];

int ans = N;
// 插入一条 a->b 的边
// 在 a 所对应的邻接表中插入节点 b 
void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ; 
}

// 返回已 u 为根的子树中的数量
// 全局变量 ans 记录答案
int dfs(int u)
{
    st[u] = true;   // 标记已经被搜索过了
    
    // res : 每个联通块的最大值
    // sum : 当前子数大小
    int sum = 1, res = 0;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            // s : 自己的子树的大小
            // sum : 自己的儿子是自己作为子树的一部分
            int s = dfs(j);
            res = max(res, s);   // 当前树和子树求做大着值   
            sum += s;            // 子树大小加上自己
        }
    }

    res = max(res, n - sum); // 当前树和上面子树求最大
    ans = min(ans, res);     // 所有子树中求最小
    return sum;     // 返回以自己为头的子树数量
}

// 求每个点删除之后的最大值, 枚举一遍求最小
int main()
{
    scanf("%d", &n);
    memset(h, -1, sizeof h);

    // n 个点右 n - 1 条边
    for (int i = 0; i < n - 1; ++ i )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    dfs(1);
    printf("%d", ans);

    return 0;
}
// 只有在约数之和(y)小与x的情况下, x才会有指向y的边
// 因此每个x最多只会向它的约数之和连一条边
// 对于每个x的言约数之和是唯一的, 因此每个点最多只会有一个父节点

#include <iostream>
#include <cstring>

using namespace std;

const int N = 250005;
int n, ans;
int h[N], w[N], e[N], ne[N], idx;
int sum[N];
bool st[N];  // 判断点的状态

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int dfs(int u)
{
    int d1 = 0, d2 = 0;
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        int d = dfs(j) + 1;     // 孩子的最长路径累加上自己
        if (d >= d1) d2 = d1, d1 = d;
        else if (d > d2) d2 = d;
    }
    // cout << u << ' ' << d1 << endl;
    ans = max(ans, d1 + d2);
    return d1;
}

// 给一个严谨点的证明, 证明所有数字组成的图是一个森林: 
// 任取图中的一个连通分量, 假设这个连通分量有环, 那么环上的每条边的父节点是要小于子节点的. 
// 假设环是x1–x2–…–xn–x1, 找到环中最大的数字xi, 那么有xi > xi-1, xi > xi+1,
// 根据建图的方式可以知道xi-1, xi+1是xi的两个不同的约数和, 但是一个数字的约数和唯一, 所以矛盾
// 所以连通分量中不存在环, 每个连通分量都是一棵树
// 其实就是每个数的约数和是唯一的，即父节点是唯一的，所以是森林。
int main()
{
    cin >> n;
    // 内层循环相当于预处理出i*j的这个子集的约数, 
    // 然后在原本的基础上累加上i*j的其他约数
    // 借用筛法的思路:我们想求i的所有约数, 反过来想i的所有倍数有哪些
    for (int i = 1; i <= n; ++ i)
        for (int j = 2; j <= n / i; ++ j)
            sum[i * j] += i;

    memset(h, -1, sizeof h);
    for (int i = 2; i <= n; ++ i)
        if (i > sum[i])
        {
            // 约数之和是1的一定是个素数, 所有数的约数里都有1, 可并不是所有数的约数都只有1
            add(sum[i], i); // sum是父节点, i是子节点
            st[i] = true;   // 因为i有父节点, 所以i不是树根
        }
    
    // 防止有多颗数, 只枚举树根
    for (int i = 1; i <= n; ++ i)
        if (!st[i]) dfs(i);

    cout << ans << endl;
    return 0;
}
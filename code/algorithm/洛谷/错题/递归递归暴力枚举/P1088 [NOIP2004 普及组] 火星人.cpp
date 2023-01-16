// 但是为了降低复杂度, 我们从深搜的部分降低其复杂度, 也就是说, 我们从给定排列直接开始
// 我们先定义一个bool数组, 用来计算是否曾经访问过这一位置, 如果访问过了, 则从1开始, 否则从给定排列开始
//
// 如果 当前层(fs[p]) 是true, 说明当前层已经来过了, 这时候从 1 开始dfs
// 找之前层没有选择过的
// 
// 每一层都是递增, 后面的层只能选择之前没有选择过的
// 上一层枚举的一定是当前层后面的数所以是递归序

#include <iostream>

using namespace std;
const int MAXN = 1e5 + 1;

int n, m;
int a[MAXN];
bool st[MAXN], vis[MAXN];

void dfs(int u)
{
    if (u == n) { m -- ; return; }
    if (!m) return;

    for (int i = (vis[u] ? 1 : a[u]); i <= n; ++ i)
        if (!st[i])
        {
            a[u] = i;
            st[i] = true;
            dfs(u + 1);
            if (!m) return;
            st[i] = false;
        }
        
    vis[u] = true; 
    return;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) scanf("%d", &a[i]);
    m ++ ;  // m+1: 完全是因为题目, 所代表的序列向后偏移一个位置
    dfs(0);
    // 0x20:32 -> '/t'
    // 0x0A:16 -> '/n'
    for (int i = 0; i < n; ++ i) printf("%d%c", a[i], (i < n - 1 ? 0x20 : 0x0A));
}
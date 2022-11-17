#include <iostream>
#include <cstirng>

using namespace std;

const int N = 100010, M = N * 2;

int n, m;
int h[N], e[M], ne[M], idx;
bool st[N];

// a 有连向 b 的边(b 是 a 的孩子)
// 1) 存储 b
// 2) b 指向 a (每次 b 指向的都是当前的对应的 a )
// 3) a 的 child 加加
// 
// 每一个 idx 都会对应一个独一无二的 h[a]
// idx 就会成为新的头
void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ; 
}

// u : 当前节点
// 已 u 节点为头遍历 u 的孩子
void dfs(int u)
{
    st[u] = true; // 标记一下, 已经被搜过了
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];       // 当前链表里的节点对应图里面节点的编号
        if (!st[j]) dfs(j); // 如果有这个节点 j 
    }
}

int main()
{
    memset(h, -1, sizeof h);
    dfs(1);
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
// 重边: 自己有两条指向相同节点的边
// 自环: 有一条边指向自己

// 宽搜: 从 1 号点开始每次扩展一层节点
//           - 1) 取队头元素
//           - 2) 扩展 t 所有能到的点
//       第一次找到的就是最短举例
// 1 { 2, 3, 4}   
// 2 { 3 }
// 3 { 4 }
// 4 {}

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], idx;
int d[N], q[N];             // 距离/队列

// 插入 a -> b 的边
void add(int a, int b)
{
    e[idx] = b; 
    ne[idx] = h[a];
    h[a] = idx++;
}

int bfs()
{
    int hh = 0, tt = 0;
    q[0] = 1;           // 队头是从 1 开始的, 因为点也是从 1 开始

    memset(d, -1, sizeof d);

    d[1] = 0;

    while (hh <= tt)
    {
        int t = q[hh++]; // 取出当前点

        // 当前节点扩展自己的各个边
        // 遍历该点的邻点, i 取出的是 idx, 通过 idx 拿到对应的值
        for (int i = h[t]; i != -1; i = ne[i]) 
        {
            int j = e[i];
            if (d[j] == -1)   // 如果 j 没有被扩展过
            {
                d[j] = d[t] + 1;    // 当前距离 = 之前的距离 + 1
                q[ ++ tt] = j;        // 自己入队列, 之后接着遍历之后的 child
            }
        }
    }
    return d[n];
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }

    cout << bfs() << endl;

    return 0;
}
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
    // h[a]:代表上一个节点, 将当前节点指向上一个节点, 
    //      让新的节点的 ne, 指向自己集合的末尾节点, 这样在遍历的时候
    //      取出的就是末尾节点
    ne[idx] = h[a]; 
    h[a] = idx++;   // h[a] a 这个槽存储当前这个集合最后一个节点编号
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

        // 
        // 1. 当前节点扩展自己的各个边, 遍历 t 指向的边, t 这个槽会优先取出自己集合内的末尾节点 i
        // 然后自己集合的末尾节点的 ne 指向了自己的前一个节点, 这样就循环起来了, 最开始的 ne 一定指向 -1
        // 遍历该点的邻点, i 取出的是 idx, 通过 idx 拿到对应的值
        // 
        // 2. 最短距离不会被后面的覆盖掉, 因为遍历到的就是最短的, 会被优先进入进 d[]
        // 当 d[j] != -1 时, 是不会被记录的  
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
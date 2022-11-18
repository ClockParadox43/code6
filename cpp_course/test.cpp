#include <iostream>

using namespace std;

const int N = 100010;

// 1) 存储边和入度
// 2) 将入度为 0 的点挑出来存入队列
// 3) 用队列处理这些入度为 0 的点
//          - 遍历 a 的所有出边, 解除 a 与 b 的联系, b 的入度 -1
//          - 如果 b 的入度等于 0 就可以入队列处理下一批
int n, m;
int h[N], e[N], ne[N], idx;
int q[N], d[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ; 
}

bool topsort()
{
    int hh = 0, tt = -1;
    
    
    for (int i = 1; i <= n; ++ i )
        if (!d[i]) q[ ++ tt] = i;

    while (hh <= tt)
    {
        int a = q[hh ++ ];          // 处理 a 的出边
        for (int i = h[a]; i != -1; i = ne[i])      // 遍历 a 所有的出边
        {
            int b = e[i];      
            d[b] -- ;
            if (d[b] == 0) q[++ tt] = b;
        }    
    }

    return tt == n - 1;
}

int main()
{
    scanf("%d%d" &n, &m);
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++ i )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        d[b] ++ ;
    }

    if (topsort()) 
        for (int i = 0; i < n; ++ i ) printf("%d", q[i]);
    else puts("-1");
    return 0;
}
// 有向无环的图称为拓扑序
// 入读为 0 , 意味着没有任何一条边指向该点
// 所以这个点没有任何依赖关系
// top 序不唯一
// 
// 思路: 将入度为 0 的点入队列, 再删去该点指向的点的所有边
// 入度: 一个点, 被指向的数量
// 所谓的 top 序列是只有从前指向后面的边,没有从后指向前面的边


#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 100010;

int n, m;
int h[N], e[N], ne[N], idx; 
int q[N], d[N];             // q[]:队列(保存入度为 0, 也就是能够输出的点), d[]: 入度为 0 

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool topsort()
{
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; ++ i )  // 将所有入度为 0 的点插入队列
        if (!d[i])
            q[ ++ tt] = i;      
    
    while (hh <= tt)                     
    {
        int a = q[hh ++ ];      
        for (int i = h[a]; i != -1; i = ne[i])   // 循环删除 a 的出边   
        {
            int b = e[i];           // t 有一条边指向  
            d[b] -- ;
            if (d[b] == 0) q[ ++ tt] = j;
        }
    }

    return tt == n - 1;    
}
// 出队列的顺序就是 top 序
// 出队列只是把指针从前往后移动一位
// 前面的顺序不变, 因此所有点遍历完后
// q 里的次序恰好 top 序
int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++ i )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        d[b] ++ ;       // b 的入度 ++ 
    }

    if (topsort())
    {
        for (int i = 0; i < n; ++ i ) printf("%d ", q[i]);
    }
    else puts("-1");
    return 0;
}
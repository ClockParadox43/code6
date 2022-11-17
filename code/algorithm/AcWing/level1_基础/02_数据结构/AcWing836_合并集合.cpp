// 并查集
// 1) 将两个并查集合并
// 2) 询问两个元素是否在一个集合中
//
// belong[x] = a : x 属于 a 这个集合
// 
// 基本原理: 每个集合用一棵树来表示, 树根的编号就是整个集合的编号, 每个
//		     节点存储它的父节点, p[x] 表示 x 的父节点

#include <iostream>

using namespace std;

const int N = 100010;
int n, q;

int p[N];

// 返回每个点的根节点
int find(int x)
{   
    if (p[x] != x)          // 只要 x 不是树根就往下走
        p[x] = find(p[x]); 
    return p[x];
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 0; i <= n; ++ i ) p[i] = i;

    while (q -- )
    {
        char op[2];
        int a, b;
        scanf("%s%d%d", op, &a, &b);
        if (op[0] == 'M') p[find(a)] = find(b);
        else 
        {
            if (find(a) == find(b)) puts("Yes");        // find(a) 返回的是 a 的祖宗节点, find(b) 返回的是 b 的祖宗节点, a 的祖宗节点变成 b 的祖宗节点
            else puts("No");
       }
    }
    return 0;
}

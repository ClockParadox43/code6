// C a b, 在点 a 和点 b 之间连一条边，a 和 b 可能相等               -> union
// Q1 a b, 询问点 a 和点 b 是否在同一个连通块中, a 和 b 可能相等    -> find
// Q2 a, 询问点 a 所在连通块中点的数量                              -> 返回爹的孩子的数量

#include <iostream>

using namespace std;

const int N = 100010;

int p[N], _size[N];

int find(int x)
{
    if (p[x] != x) x = find(p[x]);
    return p[x];
}

void _union(int a, int b)
{
    if (find(a) != find(b))           // 不属于同一个集合才需要合并
    {
        _size[find(b)] += _size[find(a)];  // a 的 size 合并进 b 
        p[find(a)] = find(b);            // a 的祖宗节点指向 b 的祖宗节点 
    }
}

//   1 2 3 4 5 
//   2 5 3 4 5
// s 1 2 1 1 3
int main()
{
    int n, q;
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; ++ i )  
    {
        p[i] = i;
        _size[i] = 1;
    }

    while (q -- )
    {
        char op[5];
        int a, b;
        scanf("%s", op);
        
        if (op[0] == 'C') 
        {
            scanf("%d%d", &a, &b);
            _union(a, b);
        }
        else if (op[1] == '1') 
        {
            scanf("%d%d", &a, &b);
            if (find(a) == find(b)) printf("Yes\n");
            else printf("No\n");
        }
        else
        {
            scanf("%d", &a);
            printf("%d\n", _size[find(a)]);
        }
    }
}

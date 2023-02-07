/* 
    有依赖的背包: 以u为根的子树在不同的体积之下, 他的最大价值是多少
                 如果枚举以u为根的子树的所有状态, 状态计算会很大
                 因为是按照体积划分, 所以说划分k划分的说体积

    没有上司的舞会其实属于最大独立集问题:
    最大独立集问题: 每一个边上有很多点和边, 但是对于每一条边上最多只会选择一个点, 
                   问在这种情况下最大的价值是什么
    战争游戏: 对于每条边至少选择一个点, 求它的最小价值

*/ 

// 
// 

// 求的是每条边至少选择一个点求最少价值
// 状态表示f[i,0]:所有以i为根的子树中选, 且点i的状态是j的所有选法
//      - f[i,0]:所有以i为根的子树不选择以i为根的最小价值
//      - f[i,1]:所有以i为根的子树不选择以i为根的最小价值

#include <iostream>

#include <cstring>

using namespace std;

const int N = 1510;
int n;
int h[N], e[N], ne[N], idx;
int f[N][2];
int st[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u)
{
    f[u][0] = 0, f[u][1] = 1;
    for (int i = h[u]; ~ i; i = ne[i])
    {
        int t = e[i];
        dfs(t);
        f[u][0] += f[t][1];
        f[u][1] += min(f[t][0], f[t][1]);
    }
}

int main()
{
    while (cin >> n)
    {
        memset(h, -1, sizeof h);
        
        idx = 0;
        memset(st, 0, sizeof st);
        for (int i = 0; i < n; ++ i)    
        {
            int id, cnt; scanf("%d:(%d)", &id, &cnt);
            while (cnt -- )
            {
                int ver; cin >> ver;
                add(id, ver);
                st[ver] = true;
            }
        }
        int root = 0;
        while (st[root]) ++ root; // 找到根节点
        dfs(root);   
        cout << min(f[root][1], f[root][0]) << endl;
    }
   
}
#include <iostream>

using namespace std;

const int N = 15;

int n;
int path[N];
bool st[N];

// u : 当前序列
// 枚举 n 范围中的数字 
// 每一层让 u 递减变化 -> 字典序要一样
void dfs(int u)
{
    if (u == n)
    {
        for (int i = 0; i < u; ++ i ) printf("%d ", path[i]);
        printf("\n");
        return ;
    }
    
    for (int i = 1; i <= n; ++ i )
    {
        if (!st[i])
        {
            path[u] = i;
            st[i] = true;
            dfs(u + 1);
            st[i] = false;
        }
    }
}

int main()
{
    scanf("%d", &n);
    dfs(0);
    return 0;
}
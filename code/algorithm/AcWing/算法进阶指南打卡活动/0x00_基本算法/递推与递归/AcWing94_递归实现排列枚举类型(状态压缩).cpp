#include <iostream>

using namespace std;

const int N = 10;

int n;
int path[N];

void dfs(int u, int st)
{
    if (u == n)
    {
        for (int i = 0; i < n; ++ i ) cout << path[i] << ' '; 
        cout << endl;
        return ;
    }
    // 枚举所有数字
    for (int i = 1; i <= n; ++ i )
    {
        if (!((st >> i) & 1))
        {
            path[u] = i;
            dfs(u + 1, st |= (1 << i));
            st ^= (1 << i);
        }
    }
}

int main()
{   
    scanf("%d", &n);
    dfs(0, 0);
    return 0;
}
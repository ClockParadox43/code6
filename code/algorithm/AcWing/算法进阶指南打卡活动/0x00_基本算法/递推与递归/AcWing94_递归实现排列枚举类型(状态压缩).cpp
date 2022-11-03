#include <iostream>

using namespace std;

const int N = 15;

int n;
int path[N];

void dfs(int u, int st)
{
    if (u == n)
    {
        for (int i = 0; i < n; ++ i ) printf("%d ", path[i]);
        cout << endl;
        return ;
    }
    
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
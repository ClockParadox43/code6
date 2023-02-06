#include <iostream>
#include <cstring>

using namespace std;

const int N = 5e4 + 10;

int n, fsum[N];
int h[N], e[N], ne[N], idx;
int d1[N], d2[N], res;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int dfs(int u)
{
    if (d1[u]) return d1[u];
    for (int i = h[u]; ~ i; i = ne[i])
    {
        int t = e[i];
        int d = dfs(t) + 1;
        if (d >= d1[u]) d2[u] = d1[u], d1[u] = d;
        else if (d > d2[u]) d2[u] = d; 
    }
    res = max(res, d1[u] + d2[u]);
    return d1[u];
}

int main()
{
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i ++ )
        for (int j = 2; j <= n / i; j ++ )
            fsum[i * j] += i;
            
    for (int i = 2; i <= n; i ++ )
        if (fsum[i] < i)
            add(fsum[i], i);
            
    for (int i = 1; i <= n; i ++ ) dfs(i);
    printf("%d\n", res);
    return 0;
}
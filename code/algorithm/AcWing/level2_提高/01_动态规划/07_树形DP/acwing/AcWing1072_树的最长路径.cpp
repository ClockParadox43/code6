#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e4 + 10;

int n, ans;
int h[N], e[2 * N], w[2 * N], ne[2 * N], idx;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ; 
}

int dfs(int u, int father)
{
    int d1 = 0, d2 = 0;     // 记录以每个根节点开始的最大距离和次大距离
    for (int i = h[u]; i != -1; i = ne[i])
    {
        int t = e[i];
        if (t == father) continue;  // 因为是无向图, a<->b, 所以可以相互走到导致死循环
                                      
        int d = dfs(t, u) + w[i];
        // 求最大和次大
        if (d >= d1) d2 = d1, d1 = d;
        else if (d > d2) d2 = d;
    }
    ans = max(ans, d1 + d2); 
    return d1;
}

int main()
{
    int n; cin >> n;
    
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; ++ i)
    {
        int a, b, c; cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    dfs(1, -1);
    cout << ans << endl;
    return 0;
}
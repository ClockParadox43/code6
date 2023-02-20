#include <iostream>
#include <vector>

using namespace std;

const int N=2e6+10;

int ans = 1;
vector<int> g[N];
bool st[N];


void dfs(int u)
{
    if (ans >= 1e6)
    {
        cout << 1000000 << endl;
        exit(0);
    }
    st[u] = true;
    for (auto x : g[u])
        if (!st[x])     // 如果孩子没有被遍历过
        {
            ans ++ ;
            dfs(x);
        }
    st[u] = false;
    
}

int main()
{
    int n, m;
    cin >> n >> m;
    while (m -- )
    {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1);
    cout << ans << endl;
    return 0;
}
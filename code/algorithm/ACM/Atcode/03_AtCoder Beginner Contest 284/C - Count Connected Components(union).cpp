#define _CRT_SECURE_NO_WARNINGS


#include <iostream>

using namespace std;
const int MAXN = 204;

int n, m;
int p[MAXN], sz[MAXN];

int find(int x)
{
    if (x != p[x]) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) { p[i] = i, sz[i] = 1; }
    while (m--)
    {
        int a, b; scanf("%d%d", &a, &b);
        int pa = find(a), pb = find(b);
        if (pa != pb)
        {
            sz[pb] += sz[pa];
            sz[pa] = 0;
            p[pa] = p[pb];
        }
    }

    int ans = 0;
    // 遍历所有点不联通就加加
    for (int i = 1; i <= n; ++i)
        if (sz[i]) ans ++;
    cout << ans << endl;
    return 0;
}
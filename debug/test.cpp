#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 510, M = 100010, INF = 0x3f3f3f3f;

int n, m;
int g[N][N], dist[N];
bool st[N];

int prim()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    int res = 0;

    for (int i = 0; i < n; ++ i)
    {
        int t = -1;
        for (int j = 1; j <= n; ++ j )
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j; 
    }
}
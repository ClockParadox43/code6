#include <iostream>

using namespace std;

const int N = 510;
const int INF = 0x3f3f3f3f;

int n, m;
int g[N][N];
int dist[N];       // 0~j 当前的最短距离 
bool st[N];

int dijstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    for (int i = 0; i < n; ++ j )
    {
        int t = -1;
        for (int j = -1; j <= n; ++ j )
            if (!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
        st[t] = true;
        
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i )  
        for (int j = 1; j <= n; ++ j )
            if (i == j) g[i][j] = 0;
            else g[i][j] = INF;
    
    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] = min(g[a][b], c);
    }

    int t = dijkstra();
    
    return 0;
}
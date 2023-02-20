
// 权重为1, 按照给定的限制bfs即可

#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;
int n, k;
int q[N];       // 记录编号
int dist[N];    // 记录距离
int bfs()
{
    memset(dist, -1, sizeof dist);
    dist[n] = 0;
    q[0] = n;

    int hh = 0, tt = 0;

    while (hh <= tt)
    {
        int t = q[hh ++ ];

        if (t == k) return dist[k];

        if (t + 1 < N && dist[t + 1] == -1)
        {
            dist[t + 1] = dist[t] + 1;
            q[ ++ tt] = t + 1;
        }
        if (t - 1 >= 0 && dist[t - 1] == -1)
        {
            dist[t - 1] = dist[t] + 1;
            q[ ++ tt] = t - 1;
        }
        if (t * 2 < N && dist[t * 2] == -1)
        {
            dist[t * 2] = dist[t] + 1;
            q[ ++ tt] = t * 2;
        }
    }

    return -1;
}

int main()
{
    cin >> n >> k;
    cout << bfs() << endl;
    return 0;
}
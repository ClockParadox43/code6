
// 如果 k 在当前点左边, 就不需要 +1, *2 的选项了

#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;
int n, k;
int q[N];
int dist[N];
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
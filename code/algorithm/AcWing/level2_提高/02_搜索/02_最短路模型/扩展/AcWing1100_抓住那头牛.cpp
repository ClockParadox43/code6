#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int N = 2e5 + 10;
struct edge
{
    int x;
}adj;
int n, k;
int dis[N];
queue<edge> q;

int main()
{
    memset(dis, -1 , sizeof dis);
    // n:农夫位置, k:牛位置
    cin >> n >> k;
    
    if (k <= n)
    {
        cout << n - k;
        return 0;
    }
    else 
    {
        int a;

        adj.x = n;
        dis[n] = 0;     // 到起点的距离
        q.push(adj);

        while (!q.empty())
        {   
            edge f = q.front(); 
            a = f.x;
            int walk[3] = {1, -1, a};
            q.pop();

            for (int i = 0; i < 3; ++ i)
            {
                int dx = f.x + walk[i];
                if (dx >= 1 && dx <= 2 * k && (dis[dx] == -1 || dis[dx] > dis[f.x] + 1))
                {
                    dis[dx] = dis[f.x] + 1;
                    adj.x = dx;
                    q.push(adj);
                }
            }
        }
        cout << dis[k] << endl;
        return 0;
    }
}
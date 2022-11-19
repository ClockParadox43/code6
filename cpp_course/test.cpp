#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010, 
int n, m;
int h[N], e[N], w[N], ne[N], idx;
int dist[N], st[N]; 

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while (q.size())
    {
        int t = q.front();
        q.pop();
        st[t] = false;
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > w[i] + dist[t])
            {
                dist[j] = w[i] + dist[t];
                if (!st[t])
                {
                    q.push(t);
                    st[t] = true;
                }
            }
        }
    }
    if (dist[n] == 0x3f3f3f3f) return -1;
    else return dist[n]; 
}

int main()
{   
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    if (dist[n] == 0x3f3f3f3f) puts("impossible");
    else printf("%d\n", dist[n]);
    return 0;
}
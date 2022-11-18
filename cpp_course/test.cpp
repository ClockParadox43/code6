#include <iostream>

using namespace std;

const int N = 100010;

int n, m;
int h[N], sz;


void down(int u)
{
    int t = u;
    if (u << 1 <= sz && h[u << 1] < h[t]) t = u << 1;
    if (u << 1 | 1 <= sz && h[u << 1 | 1] < h[t]) t = u << 1 | 1;
    if (u != t)
    {
        swap(h[u], h[t]);
        down(t);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i ) scanf("%d", &h[i]);
    sz = n;
    
    for (int i = sz >> 1; i; -- i ) down(i);
}
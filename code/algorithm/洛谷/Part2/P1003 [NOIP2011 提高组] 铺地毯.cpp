#include <isotream>
#include <cstring>

using namespace std;

const int N = 10005;

int q[N][N];

int main()
{
    memset(v, -1, sizeof v);
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++ i )
    {
        int a, b, g, k; scanf("%d%d%d%d", &a, &b, &g, &k);
        for (int x = a; x <= a + g; ++ x)
            for (int y = b; y <= b + k; ++ y)
                v[x][y] = i;
    }
    int x, y; scanf("%d%d", &x, &y);
    printf("%d", q[x][y]);
    return 0;
}

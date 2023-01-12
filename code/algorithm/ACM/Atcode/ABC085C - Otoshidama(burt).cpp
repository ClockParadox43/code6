#include <iostream>
#include <algorithm>

using namespace std;
const int MAXN = 2010;

int n, y;
int bills[3] = { 10000, 5000, 1000 };
// int bills[3] = { 1000, 5000, 10000 };
bool flag = false;

void dfs(int u, int rest_n, int rest, int cntA, int cntB, int cntC)
{
    if (flag) return;
    if (rest < 0 || rest_n < 0) return;
    if (u >= 3)
    {
        if (!rest && !rest_n)
        {
            printf("%d %d %d\n", cntA, cntB, cntC);
            flag = true;
        }
        return;
    }

    for (int i = 0; i <= rest_n && bills[u] * i <= rest; ++i)
    {
        if (i && bills[u] == bills[0]) cntA = i;
        else if (i && bills[u] == bills[1]) cntB = i;
        else if (i && bills[u] == bills[2]) cntC = i;
        dfs(u + 1, rest_n - i, rest - i * bills[u], cntA, cntB, cntC);
    }
}

int main()
{
    scanf("%d%d", &n, &y);

    dfs(0, n, y, 0, 0, 0);

    if (!flag) printf("%d %d %d", -1, -1, -1);
    return 0;
}
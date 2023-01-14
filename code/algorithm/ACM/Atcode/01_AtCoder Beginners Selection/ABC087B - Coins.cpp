#include <iostream>

using namespace std;

int yen[3] = { 500, 100, 50 };
int num[3];
int x;
int ans = 0;

// 当前面值也对应着, 数量
void dfs(int u, int rest)
{
    if (rest < 0) return;
    if (u == 3)
    {
        if (!rest) ans += 1;
        return;
    }

    for (int i = 0; i * yen[u] <= rest && i <= num[u]; ++ i)
        dfs(u + 1, rest - yen[u] * i);
}


int main()
{
    for (int i = 0; i < 3; ++i)
        scanf("%d", &num[i]);

    scanf("%d", &x);
    dfs(0, x);
    cout << ans << endl;
    return 0;
}
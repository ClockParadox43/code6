// 多了一种状态:
// 卖出股票后, 你无法在第二天买入股票(即冷冻期为 1 天)
#include <iostream>
#include <cstring>

using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m;
int f[N][3];
int w[N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> w[i];
    
    f[0][0] = f[0][1] = -INF, f[0][2] = 0;
    for (int i = 1; i <= n; ++ i)
    { 
        f[i][0] = max(f[i - 1][0], f[i - 1][2] - w[i]);
        f[i][1] = f[i - 1][0] + w[i];
        f[i][2] = max(f[i - 1][2], f[i - 1][1]);
    }   
    cout << max(f[n][1], f[n][2]) << endl;
    return 0;
}
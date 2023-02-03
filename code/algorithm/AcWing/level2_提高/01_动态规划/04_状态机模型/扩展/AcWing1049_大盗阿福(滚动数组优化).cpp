#include <iostream>
#include <cstring>

#define MAXK 103
using namespace std;

int n, k, ans;
int f[2][MAXK];

int main()
{
    cin >> n >> k;
    memset(f, 0xcf, sizeof f);
    f[0][0] = 0;
    for (int i = 1; i <= n; ++ i)
    {
        int w; cin >> w;
        for (int j = k; j; -- j)
        {
            f[0][j] = max(f[0][j], f[1][j] + w);
            f[1][j] = max(f[1][j], f[0][j - 1] - w);
        }
    }
    for (int i = 0; i <= k; ++ i) 
        ans = max(ans, f[0][i]);
    cout << ans << endl;
    return 0; 
}
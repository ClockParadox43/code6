#include <iostream>

#define MAXN 20001
using namespace std;

int n, m;
int w[MAXN];
int f[2][MAXN];

int main()
{
    cin >> m >> n;
    for (int i = 1; i <= n; ++ i) cin >> w[i];
    for (int i = 1; i <= n; ++ i) 
        for (int j = 0; j <= m; ++ j)
        {   
            f[i & 1][j] = f[i - 1 & 1][j];
            if (j >= w[i]) f[i & 1][j] = max(f[i & 1][j], f[i - 1 & 1][j - w[i]] + w[i]);
        }
    cout << m - f[n & 1][m] << endl;
    return 0;   
}
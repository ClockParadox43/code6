#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;

int T, n;
int w[N];
int f[2][2];

int main()
{
    cin >> T;
    while (T -- )
    {
        memset(f, 0xcf, sizeof f);
        f[0][0] = 0;
        cin >> n;
        for (int i = 1; i <= n; ++ i) cin >> w[i];
        for (int i = 1; i <= n; ++ i)
        {
            f[i & 1][0] = max(f[(i - 1) & 1][0], f[(i - 1) & 1][1]);
            f[i & 1][1] = f[(i - 1) & 1][0] + w[i];
        }
        cout << max(f[n & 1][0], f[n & 1][1]) << endl;
    }   
    return 0;
}
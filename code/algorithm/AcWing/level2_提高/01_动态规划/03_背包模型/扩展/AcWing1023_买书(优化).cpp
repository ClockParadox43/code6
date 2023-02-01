#include <iostream>

using namespace std;

const int N = 5, M = 1010;

int n = 4, m;
int v[N] = {0, 10, 20, 50, 100};
int f[M];

int main()
{
    cin >> m;

    f[0] = 1;
    for (int i = 1; i <= n; ++ i)
        for (int j = v[i]; j <= m; ++ j)
            f[j] += f[j - v[i]];

    cout << f[m] << endl;
    return 0;
}
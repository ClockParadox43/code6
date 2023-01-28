#include <iostream>

using namespace std;

const int N = 1010;

int n;
int a[N];
int f[N][2];

int main()
{
    //input
    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> a[i];

    //dp
    for (int i = 1; i <= n; ++ i)
    {
        f[i][0] = f[i][1] = 1;
        for (int k = 1; k < i; ++ k)
        {
            if (a[k] < a[i]) f[i][0] = max(f[i][0], f[k][0] + 1);
            if (a[k] > a[i]) f[i][1] = max(f[i][1], max(f[k][0], f[k][1]) + 1);
        }
    }

    //find result from all final states
    int res = 0;
    for (int i = 1; i <= n; ++ i) res = max(res, max(f[i][0], f[i][1]));
    cout << res << endl;

    return 0;
}
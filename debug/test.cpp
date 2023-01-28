#include <iostream>

using namespace std;

const int MAXN = 103;

int n;
int w[MAXN];
int f[MAXN], fl[MAXN];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) scanf("%d", &w[i]);
    
    for (int i = 0; i < n; ++ i)
    {
        f[i] = 1;
        for (int j = 0; j < i; ++ i)
            if (w[i] > w[j]) f[i] = max(f[i], f[j] + 1);
    }

    for (int i = n - 1; i >= 0; -- i)
    {
        f[i] = 1;
        for (int j = n - 1; j > i; -- j)
            if (w[i] > w[j]) f[i] = max(f[i], f[j] + 1);
    }

    int range = 0;
    for (int i = 0; i < n; ++ i) range = max(range, f[i] + f[j] - 1);
    
    cout << n - range;
    return 0;
}
#include <iostream>

using namespace std;

const int MAXN = 1010, MAXM = 503;

int n, W, Wl;
int f[MAXN][MAXM];

int main()
{
    cin >> W >> Wl >> n;    // W:精灵球花费, Wl:血量花费        
    for (int i = 0, w, wl; i < n; ++ i)
    {
        cin >> w >> wl;
        for (int j = W; j >= w; -- j)
            for (int k = Wl - 1; k >= wl; -- k)
                f[j][k] = max(f[j][k], f[j - w][k - wl] + 1);
    }

    int k = Wl - 1;
    // 找最小, 找到第一个不相等的就是
    while (k > 0 && f[W][k - 1] == f[W][Wl - 1]) k -- ;
    cout << f[W][Wl - 1] << ' ' << Wl - k << endl;
    return 0;
}
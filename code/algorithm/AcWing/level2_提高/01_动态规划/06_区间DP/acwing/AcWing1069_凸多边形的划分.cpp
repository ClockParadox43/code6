// 分析:
// 将三角形进行划分后可以发现两边的凸多边形没有交集, 完全独立
// 因此所有这样的方案都可以分为三个部分, 划分后, 取min(左部分, 三角形三边积, 右半部分)
// 划依据:哪些三角形属于l~r这些范围的边
#include <iostream>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 55, M = 35, INF = 1e9;


int n;
int w[N];
ll f[N][N][M];  // 例: 12 * 12 = 144, 那么第3维存的数就是144

void add(ll a[], ll b[])
{
    static ll c[M];
    memset(c, 0, sizeof c);
    for (int i = 0, t = 0; i < M; ++ i)
    {
        t += a[i] + b[i];
        c[i] = t % 10;
        t /= 10;
    }
    memcpy(a, c, sizeof c);
}

void mul(ll a[], ll b)
{
    static ll c[M];
    memset(c, 0, sizeof c);
    ll t = 0;
    for (int i = 0; i < M; ++ i)
    {
        t += a[i] * b;
        c[i] = t % 10;
        t /= 10;
    }
    memcpy(a, c, sizeof c);
}

int cmp(ll a[], ll b[])
{
    for (int i = M - 1; i >= 0; -- i)
        if (a[i] > b[i]) return 1;
        else if (a[i] < b[i]) return -1;
    return 0;
}

void print(ll a[])
{
    int k = M - 1;
    while (k && !a[k]) k -- ;
    while (k >= 0) cout << a[k -- ];
    cout << endl;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    
    ll tmp[M];
    for (int len = 3; len <= n; ++len)
        for (int l = 1; l + len - 1 <= n; ++l)
        {
            int r = l + len - 1;
            // 注意这里是高精度, 相当于1后面跟一堆0
            f[l][r][M - 1] = 1;
            // l+1:因为是三角形, 中间的点的权重
            for (int k = l + 1; k < r; ++k)
            {
                memset(tmp, 0, sizeof tmp);
                // 三角形三条边
                tmp[0] = w[l];
                mul(tmp, w[k]);
                mul(tmp, w[r]); 
                // 之前集合的最优解
                add(tmp, f[l][k]);
                add(tmp, f[k][r]);
                if (cmp(f[l][r], tmp) > 0)
                    memcpy(f[l][r], tmp, sizeof tmp);
                // f[l][r] = min(f[l][r], f[l][k] + f[k][r] + w[l] * w[k] * w[r]);
            }
        }
    print(f[1][n]);
    return 0;

}
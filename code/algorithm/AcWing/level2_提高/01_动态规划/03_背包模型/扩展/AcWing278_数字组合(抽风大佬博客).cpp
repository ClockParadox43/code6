// 链接：https://www.acwing.com/solution/content/38990/
// (NTT, 生成函数) O(mlogm)
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 40005;
const int mod = 998244353, G = 3;

int n, m;
int last = -1, lim, rev[N];
int a[N], b[N], rt[N];

inline void bmod(int& x) {x += x >> 31 & mod;}
inline void swap(int& a, int& b) {a ^= b ^= a ^= b;}
inline void reverse(int* st, int* ed) {while (st < --ed) swap(*st++, *ed);}

int inv(int x, int k = mod - 2)
{
    int r = 1;
    while (k)
    {
        if (k & 1) r = (ll)x * r % mod;
        x = (ll)x * x % mod;
        k >>= 1;
    }
    return r;
}

struct NT
{
    int inverse[N];
    void prework(int n)
    {
        inverse[1] = 1;
        for (int i = 2; i <= n; i ++ )
            bmod(inverse[i] = -(ll)inverse[mod % i] * (mod / i) % mod);
    }
    int operator() (const int x) {return inverse[x];}
} Inv;

/*NTT板子*/ 
void prework(int n)
{
    if (last == n) return;
    last = n, lim = 1;
    while (lim <= n) lim <<= 1;
    for (int i = 0; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1 ? lim >> 1 : 0);
    for (int k = 2, i; k <= lim; k <<= 1)
    {
        rt[i = k >> 1] = 1;
        ll v = inv(G, (mod - 1) / k);
        for (int j = i + 1; j < k; ++j) rt[j] = rt[j - 1] * v % mod;
    }
}

void NTT(int* f, bool flag = true)
{
    if (!flag) reverse(f + 1, f + lim);
    for (int i = 0; i < lim; i ++ )
        if (i < rev[i])
            swap(f[i], f[rev[i]]);
    int x, *bf;
    for (int k = 2, len, i, j; k <= lim; k <<= 1)
        for (len = k >> 1, i = 0; i < lim; i += k)
            for (bf = rt + len, j = i; j < i + len; j ++, bf ++ )
            {
                x = (ll)f[len + j] * *bf % mod;
                bmod(f[len + j] = f[j] - x);
                bmod(f[j] += x - mod);
            }
    if (flag) return;
    ll v = inv(lim);
    for (int i = 0; i < lim; i ++ ) f[i] = f[i] * v % mod;
}

void fmul(int n, int m, int* f, int* g, int* res)
{
    static int tf[N], tg[N]; prework(n + m);
    memcpy(tf, f, n << 2), memset(tf + n, 0, lim - n << 2), NTT(tf);
    memcpy(tg, g, m << 2), memset(tg + m, 0, lim - m << 2), NTT(tg);
    for (int i = 0; i < lim; i ++ ) res[i] = (ll)tf[i] * tg[i] % mod;
    NTT(res, false);
}

void finv(int n, int* f, int* g)
{
    static int tf[N];
    if (n == 1) return (void)(g[0] = inv(f[0]));
    finv(n + 1 >> 1, f, g), prework(n << 1);
    memcpy(tf, f, n << 2);
    memset(tf + n, 0, lim - n << 2);
    memset(g + n, 0, lim - n << 2);
    NTT(tf), NTT(g);
    for (int i = 0; i < lim; i ++ ) bmod(g[i] = (2 - (ll)tf[i] * g[i] % mod) * g[i] % mod);
    NTT(g, false);
    memset(g + n, 0, lim - n << 2);
}

void fln(int n, int* f, int* g)
{
    static int tf[N];
    finv(n, f, g);
    for (int i = 0; i < n; i ++ ) tf[i] = (i + 1ll) * f[i + 1] % mod;
    fmul(n, n, tf, g, tf);
    for (int i = 1; i < n; i ++ ) g[i] = (ll)tf[i - 1] * Inv(i) % mod;
    g[0] = 0;
}

void fexp(int n, int* f, int* g)
{
    static int tf[N];
    if (n == 1) return (void)(g[0] = 1);
    fexp(n + 1 >> 1, f, g);
    memset(tf, 0, n << 2);
    fln(n, g, tf), --tf[0];
    for (int i = 0; i < n; i ++ ) tf[i] = (f[i] - tf[i] + mod) % mod;
    fmul(n, n, g, tf, g);
    memset(g + n, 0, lim - n << 2);
}

/**********/

int t[N];
int main()
{
    scanf("%d%d", &n, &m);
    Inv.prework(m);
    for (int i = 0; i < n; i ++ )
    {
        int v;
        scanf("%d", &v);
        t[v] ++ ;
    }
    for (int i = m; i; --i)
        if (t[i])
            for (int k = 1; i * k <= m; ++k)
            {
                int& x = a[i * k], y = (ll)t[i] * Inv(k) % mod;
                bmod(x += k & 1 ? y - mod : -y);
            }
    fexp(m + 1, a, b);
    printf("%d\n", b[m]);
    return 0;
}

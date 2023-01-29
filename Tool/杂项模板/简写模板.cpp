#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define e(a) exit(a)
#define rep(i, a, n) for(int i=a;i<n;++i)
#define repe(i, a, n) for(int i=a;i<=n;++i)
#define per(i, a, n) for (int i=n-1;i>=a;--i)
#define pere(i, a, n) for (int i=n;i>=a;--i)
#define mcpy(a, b) memcpy(a,b,sizeof b)
#define mone(x) memset(x,-1,sizeof x)
#define mmax(x) memset(x,0x3f,sizeof x)
#define mmin(x) memset(x,-0x3f,sizeof x)
#define mzero(x) memset(x,0,sizeof x)
#define bg begin()
#define ed end()
#define ft front()
#define all(x) x.bg,x.ed
#define iter iterator
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define sz(x) (int)x.size()
#define p(x) cout<<x<<endl
#define pp(x) cout<<x.fi<<' '<<x.ed<<endl
#define in() freopen("in.txt", "r", stdin)
#define out() freopen("out.txt", "w", stdout)
#define gtime() cout << "time:" << 1.0 * clock() / CLOCKS_PER_SEC << " s." << endl
#define gspace(x) cout << 1.0 * sizeof x / 1024 / 1024 << endl

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef map<int, int> mii;

ll mod(ll a, ll b) { return (a % b + b) % b; }

int lb(int x) { return x & -x; }

ll qmi(ll a, ll b, ll p) 
{
    ll res = 1;
    a %= p;
    while (b) 
    {
        if (b & 1) res = res * a % p;
        b >>= 1, a = a * a % p;
    }
    return res;
}

ll qmul(ll a, ll b, ll p) 
{
    ll res = 0;
    a %= p;
    while (b) 
    {
        if (b & 1)res = (res + a) % p;
        b >>= 1, a = (a + a) % p;
    }
    return res;
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
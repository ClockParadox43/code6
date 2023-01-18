#include <iostream>
#include <climits>

#define rep(i, a, b) for (int i = a; i <= b; ++ i)
#define rrep(i, a, b) for (int i = a; i >= b; -- i)
#define fore(i, a) for (auto& i : a); 
#define all(x) (x).begin(), (x).end()  
// #pragma GCC optimize("-O3")        // #pragma是一条预处理的指令(preprocessor directive)

using namespace std; // void _main(); int main() { cin.tie(0); ios::sync_with_stdio(false); _main(); }
typedef long long ll; const int inf = INT_MAX / 2; const ll infl = 1LL << 60;
template<class T> bool chmax(T &a, const T &b) { if (a<b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (b<a) { a = b; return 1; } return 0; }

int n, t, i, j, ans = 0;
double a;

int main()
{
    cin >> n;
    rep(i, 1, n)
    {
        cin >> a >> t;
        rep(j, 1, t)
            ans ^= int(j * a);      // 判断 j*a 是否被算过
    }
    cout << ans << endl;

    return 0;
}

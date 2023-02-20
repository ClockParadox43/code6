#include <iostream>

using namespace std;

typedef long long ll;

int t;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> t;
    while (t -- )
    {
        ll n; cin >> n;
        for (ll i = 2; i < n; ++ i)     
            if (n % i == 0) 
                if ((n / i) % i == 0)   // 如果(n/i)能够整除i, 那么就是 i*i是p的质因数
                {
                    ll p = i;
                    ll q = n / p / p;
                    cout << p << ' ' << q << endl;
                    break;
                }
                else            // 否则就是 n/q = (i*i)
                {
                    ll q = i;
                    ll p = (ll)sqrt(n / q);
                    cout << p << ' ' << q << endl;
                    break;
                }
    }
    return 0;
}
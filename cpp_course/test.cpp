#include <iostream>

using namespace std;
typedef long long ll;

int main()
{
    ll n = 20, num = 1, ans = 0;
    for (ll i = 1; i <= n; ++ i)
    {
        num *= i;
        ans += num;
    }

    cout << ans;
    return 0;
}
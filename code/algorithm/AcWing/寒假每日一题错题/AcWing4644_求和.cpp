#include <iostream>

using namespace std;

typedef long long LL;
const int N = 200010;

int n;
LL sum, ans;
LL q[N];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i ) { cin >> q[i], sum += q[i]; }
    for (int i = 0; i < n; ++ i ) ans += (sum - q[i]) * q[i];
    cout << ans / 2 << endl;
    return 0;
}




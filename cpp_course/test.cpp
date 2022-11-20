#include <iostream>
#include <unordered_map>

using namespace std;

const int mod = 1e9 + 7;
typedef long long LL;

int main()
{
    int q; scanf("%d", &q);
    unordered_map<LL, int> primes;
    while (q -- )
    {
        int x; scanf("%d", &x);
        for (int i = 2; i <= x / i; ++ i )
            while (n % i == 0) x /= i, primes[i] ++ ;
        if (x > 1) primes[x] ++ ; 
    }
    int res = 1;
    for (atuo p : primes) 
    {
        int a = p.first, b = p.second;
        LL t = 1;
        while (b >= 0) 
        {
            t += a * b % mod;
            -- b;
        } 
        res = res * t % mod;
    }
    cout << res << endl;
    return 0;
}
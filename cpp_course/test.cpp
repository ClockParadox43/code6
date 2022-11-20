// 2) 约数个数

#include <iostream>
#include <unordered_map>

using namespace std; 

typedef long long LL;
const int N = 1e9 + 7;

int main()
{
    int n; scanf("%d", &n);
    unordered_map<LL, int> primes;
    while (n -- )
    {
        int x; scanf("%d", &x);
        for (int i = 2; i <= n / i; ++ i )
            while (x % i == 0)
                x /= i, primes[i] ++ ;  
        if (x > 1) primes[x] ++ ;
    }
    
    LL res = 1;
    for (auto x : primes) res = (res * (x.second + 1)) % mod; 
    cout << res << endl;
    return 0;
}
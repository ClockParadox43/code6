#include <iostream>

using namespace std;
typedef long long ll;
const int N = 3e6 + 10;

int primes[N], cnt;
bool st[N];

void euler()
{
    int n = 3e6;
    for (int i = 2; i <= n; ++ i)
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; ++ j)
        {
            st[primes[j] * i] = true;   // p[j]是p[j]*i的最小质因数, 用最小质因数去筛和数
            
            // 1) 当i%p[j]!=0, 说明此时遍历到的p[j]不是i的质因子, 只可能是p[j]<i的最小质因子, 所以p[j]*i的最小质因子是p[j]
            // 2) 当i%p[j]==0, 说明p[j]是i和p[j]*i的最小质因子, 之后用st[p[j + 1] * i] = true去筛合数时
            //    就不是用最小质因子去更新来, 因为 i 有最小质因子p[j] < p[j + 1], 此时退出循环, 避免重复筛选
            if (i % primes[j] == 0) break;
        }
    }
}

int main()
{
    euler();
    int t; ll n;
    cin >> t;
    
    // 用最小质数去筛
    while (t -- )
    {
        cin >> n;
        for (int i = 0; i < cnt; ++ i)
            if (n % primes[i] == 0)
            {
                if ((ll)(n / primes[i]) % primes[i] == 0)
                {
                    int p = primes[i];
                    ll q = n / p / p;
                    cout << p << ' ' << q << endl;
                    break;
                }
                else 
                {
                    int q = primes[i];
                    ll p = (ll)sqrt(n / primes[i]);
                    cout << p << ' ' << q << endl;
                    break;
                }
            }
        
    }
    return 0;
}
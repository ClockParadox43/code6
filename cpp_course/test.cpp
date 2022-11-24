#include <iostream>

using namespace std;

const int mod = 1e9 + 7;

int qmin(int a, int b, int p)
{    
    int res = 1 % mod;
    for (; b; b >>= i)
    {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;   
    } 
    return res;
}

int main()
{
    int n; scanf("%d", &n);
    while (n -- )
    {
        int a, b, p; scanf("%d%d%d", &a, &b, &p);
        cout << qmin(a, b, p) << endl;
    }
    return 0;
}
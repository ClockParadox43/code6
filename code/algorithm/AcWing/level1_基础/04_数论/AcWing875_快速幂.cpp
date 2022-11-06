#include <iostream>

using namespace std;

typedef long long LL;

int qmi(int a, int b, int p)
{
    int ans = 1 % p; 
    for (; b ; b >>= 1 )
    {
        if (b & 1) ans = (LL)ans * a % p;
        a = (LL)a * a % p;
    }
    return ans;
}

int main()
{
    int _ ;
    scanf("%d", &_ );
    
    while (_ -- )
    {
        int a, b, p;
        scanf("%d%d%d", &a, &b, &p);
        printf("%d\n", qmi(a, b, p));
    }
    
    return 0;
}
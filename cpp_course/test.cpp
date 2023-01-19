#include <iostream>

using namespace std;

int main()
{
    scanf("%d", &n);
    
    int ans = 0; 
    for (int i = 2; i < n / i; ++ i)
    {
        if (n % i == 0) 
        {
            int s = 0;
            while (n % i)
                n /= i, ++ i;
            ans = max(n, ans);
        }
        if (n > 1) ans = max(n, ans);
    }
    cout << ans << endl;
    return 0;
}
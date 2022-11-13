#include <iostream>

using namespace std;

const int N = 100010;

int s[N];

int main()
{
    int n, _;
    scanf("%d%d", &n, &_);
    
    for (int i = 1; i <= n; ++ i ) scanf("%d", &s[i]);
    for (int i = 1; i <= n; ++ i ) s[i] = s[i] + s[i - 1];
    
    while (_ -- )
    {
        int b, e;
        scanf("%d%d", &b, &e);
        printf("%d\n", s[e] - s[b - 1]);
    }
    
    return 0;
}
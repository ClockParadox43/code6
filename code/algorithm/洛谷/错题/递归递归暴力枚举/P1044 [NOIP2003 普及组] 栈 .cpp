#include <iostream>

using namespace std;
const int MAXN = 30;

int a, b;
int w[MAXN];

int get_bit(int x)
{
    while (x)
    {
        int t = x % 10;
        w[t] ++ ;
        x /= 10;
    }
}

int main()
{
    scanf("%d%d", &a, &b);
    
    for (int i = a; i <= b; ++ i)
        get_bit(i);
    for (int i = 0; i <= 9; ++ i) printf("%d ", w[i]);
    return 0;
}
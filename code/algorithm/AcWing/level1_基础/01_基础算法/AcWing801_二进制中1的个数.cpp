#include <iostream>

using namespace std;

int lowbit(int x)
{
    return x & -x;
}

int main()
{
    int n;
    scanf("%d", &n);

    while (n -- )
    {
        int res = 0;
        int x;
        scanf("%d", &x);
        while (x)
        {
            x -= lowbit(x);     // 每次减去一个最右侧的 1 
            ++ res ; 
        }
        cout << res << ' ';
    }

    return 0;
}
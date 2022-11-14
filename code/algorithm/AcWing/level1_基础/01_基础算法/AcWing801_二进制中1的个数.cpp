#include <iostream>

using namespace std;

int lowbit(int x)
{
    return x & (~x + 1);
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

        // 例:5
        // 只能循环 2 次
        // 第一次减去 001, 第二次减去 100
        while (x)
        {
            x -= lowbit(x);     // 每次减去一个最右侧的 1 
            ++ res ; 
        }
        cout << res << ' ';
    }

    return 0;
}
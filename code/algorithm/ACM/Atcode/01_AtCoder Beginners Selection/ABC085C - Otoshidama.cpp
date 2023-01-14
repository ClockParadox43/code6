#include <iostream>
 
using namespace std;
 
int n, y;
 
int main()
{
    scanf("%d%d", &n, &y);
 
    // 给了 n 张钱, 判断是否可以用 10000, 5000, 1000 凑出
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n - i; ++j)
        {    
            int k = n - i - j;
            int total = 10000 * i + 5000 * j + 1000 * k;
            if (total == y)
            {
                printf("%d %d %d", i, j, k); 
                return 0;
            }
        }

    printf("%d %d %d", -1, -1, -1);
    return 0;
}
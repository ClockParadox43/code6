#include <iostream>

using namespace std;

const int N = 10010;
int f = -1;
int g[N][5];

// 将他们抽象成方格记录下来, 算出左下角和右上角的坐标
int main()
{
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++ i )
    {
        scanf("%d%d%d%d", &g[i][1], &g[i][2], &g[i][3], &g[i][4]);
        g[i][3] += g[i][1];
        g[i][4] += g[i][2];
    }
    
    int x, y; scanf("%d%d", &x, &y);
    // 倒着搜, 因为后面的会把前面的覆盖
    for (int i = n; i >= 1; -- i )
        if (x >= g[i][1] && y >= g[i][2] && x <= g[i][3] && y <= g[i][4]) 
        {
            printf("%d", i);
            f = 1;
            break;
        }
    
    if (f == -1) cout << f;
    
    return 0;
}
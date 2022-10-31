// 给定一个整数 n，将数字 1∼n 排成一排, 将会有很多种排列方法
// 数据范围:
// 1 ≤ n ≤ 7
// 时间复杂度: O(n!)
  
#include <iostream>

using namespace std;

const int N = 7;

int n;
int path[N];
int st[N];

void dfs(int u)
{
    if (u == n)     // 当走到最后一个位置时, 说明所有位置填满了
    {
        for (int i = 0; i < n; ++ i ) printf("%d ", path[i]);
        printf("\n");
        return; 
    }

    for (int i = 1; i <= n; ++ i )
    {
        if (!st[i])
        {
            path[u] = i;      
            st[i] = true;
            dfs(u + 1);         // 继续枚举下一个路径

            // 还原现场
            // path[u] = 0, path[u] 上所有数会被不断覆盖掉, 所以 path[u] 可以不用还原现场
            st[i] = false;
        }
    }
}

int main()
{
    scanf("%d", &n);
    dfs(0);
    return 0;
}
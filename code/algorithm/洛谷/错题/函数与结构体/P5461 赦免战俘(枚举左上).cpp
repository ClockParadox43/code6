// 本题基本思路是分治, 代码可以通过递归来实现, 
// 每次递归将左上方的正方形清零, 并再次递归剩余的三个正方形, 当正方形的边长为 2 时结束递归

#include <iostream>

using namespace std;
const int MAXN = 1050;

int n, a = 1;   // 边长
int g[MAXN][MAXN];


// a:表示边长, x/y:正方形的横纵坐标
void dfs(int a, int x, int y)
{
    if (a == 2)
    {
        g[x][y] = 0;        // 找到可以赦免的坐标
        return;
    }
    // x+a/2-1: 坐标 + 方格分开后边长的上限
    for (int i = x; i <= x + a / 2 - 1; ++ i)
        for (int j = y; j <= y + a / 2 - 1; ++ j)
            g[i][j] = 0;
    
    // 递归剩下三个正方形
    dfs(a / 2, x + a / 2, y);
    dfs(a / 2, x + a / 2, y + a / 2);
    dfs(a / 2, x, y + a / 2);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) a *= 2;   // 计算正方形边长
    
    for (int i = 1; i <= a; ++ i)   
        for (int j = 1; j <= a; ++ j)
            g[i][j] = 1;    // 将数组先赋值为 1

    dfs(a, 1, 1);
    for (int i = 1; i <= a; ++ i)
    {
        for (int j = 1; j <= a; ++ j)
            cout << g[i][j] << ' ';
        puts("");
    }    
    return 0;
}


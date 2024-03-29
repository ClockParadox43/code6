#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>

using namespace std;
const int MAXN = 1003;

int a[MAXN][MAXN];

// 指数和小方块还有递归是什么关系 ?
// 每次递归加去一个 2 的 n-1 次方, 走 2 的 n-1 次方步又能形成一个方块
// 它以 2^n 的速度增长, 每次形成一个方块, 
// 再找到它每次形成的方块的 左下, 右下, 右上
// 
// 思路:分治所有不同状态小方块, 例:分治(6,0)开头的, (4,0), (0,0)开头的 .. .. 
//     不只是待 0 的, 周围的方块, 如以(4,2) 开头, 它们都会看到 ( (4,0)是左上角, 它会找到它的右上角) 
//     找到它们各自需要排除的点 (最终 n=0, 缩减到 一个点位置)
// 
// 将矩阵分四部分, 左上角不处理(合法), 只处理右上, 左下, 右下
// n = 0: 时无法再分割, 在 数组相应的坐标加上标记
// n != 0: 矩阵可以继续分割, 确定好剩下 3 矩阵左上角坐标, 继续递归执行下去
//   
// 已知 左上角坐标(x,y), 那么右上(x, y+2^(n-1))
// 左下(x+2^(n-1)), 右下(x+2^(n-1), y+(n-1))
// 如果下次给定的 n 是边长, 那么我们就求它的指数, 或者直接递归除以2
// 2^(3-1) -> 下一个坐标 n-1, 4 + 2^(2-1)
// (4, 0)               (6, 0)               -> 递归得到左下角的坐标
// x,y 坐上角左边
void cal(int x, int y, int n)
{
    if (!n) a[x][y] = 1;
    else
    {
        cal(x + (1 << n - 1), y, n - 1);    // 左下角
        cal(x, y + (1 << n - 1), n - 1);    // 右上角
        cal(x + (1 << n - 1), y + (1 << n - 1), n - 1); // 右下角
    }
}

// 因为该题用位运算模拟下标, 位运算从 0 开始, 这里也从 0 开始
int main()
{
    int n; scanf("%d", &n);
    cal(0, 0, n);

    for (int i = 0; i < 1 << n; ++ i)
    {
        for (int j = 0; j < 1 << n; ++ j)
            printf("%d ", a[i][j]);
        puts("");
    }
    return 0;
}
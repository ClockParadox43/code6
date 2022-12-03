// 核心思想: 异或 - 不进位加法
//          那么等式与等式之间的异或要一起进行才能保证等式左右两边依然是等式关系
//   a^b^c = x
//     d^f = y
//    则
//  a^b^c^d^f = x^y
// 1 左下角消 0
//   1.1 枚举列
//   1.2 找第一个非零行
//   1.3 交换
//   1.4 把同列下面行消零(异或)
// 2 判断3种情况
//   2.1 唯一解
//   2.2 秩<n
//   2.2.1 有矛盾 无解
//   2.2.2 无矛盾 无穷多解

#include <iostream>

using namespace std;

const int N = 110;

int n;
int a[N][N];

int gauss()
{
    int c, r;
    for (c = 0, r = 0; c < n; ++ c )
    {
        // 找主元
        int t = -1;
        for (int i = r; i < n; ++ i )
            if (a[i][c])                    // 找开头是 1 的行
            {
                t = i;
                break;
            }
        
        if (t == -1) continue;

        // 交换主元行
        for (int j = c; j <= n; ++ j ) swap(a[r][j], a[t][j]);

        // 左下角消
        for (int i =  r + 1; i < n; ++ i )
            if (a[i][c])  // 下一行已经是 0 的就不用管了, 需要管不是 0 的行
                for (int j = n; j >= c; -- j )
                    a[i][j] ^= a[r][j];

        // 处理完后行数往下移动一位
        ++ r;   
    } 

    // 判断
    if (r < n) 
    {
        for (int i = r; i < n; ++ i )
            if (a[i][n]) return 2;
        return 1;
    }

    // 消右上角
    // if (a[i][j]): 如果是 0, 就不用下面的 a[i][j] 来异或 a[i][j]
    // 如果不是 0, 才需要用第 j 行第 j 列 a[j][j] 来异或第 i 行第 j 列 a[i][j]
    // 进而进行整行 row[i]^row[j] 间接导致 a[i][n]^a[j][n]
    for (int i = n - 1; i >= 0; -- i )
        for (int j = i + 1; j < n; ++ j )   
            if (a[i][j]) a[i][n] ^= a[j][n]; 

    return 0;
}

int main()
{
    scanf("%d", &n);
    
    for (int i = 0; i < n; ++ i )
        for (int j = 0; j <= n; ++ j )
            scanf("%d", &a[i][j]);          // 输入方程组

    int t = gauss();

    if (t == 0)
        for (int i = 0; i < n; ++ i ) printf("%d\n", a[i][n]);
    else if (t == 1) puts("Multiple sets of solutions");
    else puts("No solution");

    return 0;
}

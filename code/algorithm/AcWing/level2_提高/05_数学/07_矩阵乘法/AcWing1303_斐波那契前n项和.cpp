// 如果是求第 n 项, 有一个矩阵快速幂的做法: 
//      - 用快速幂, 将求第 n 项转化成求矩阵的 n 次方的形式
// 构造一个矩阵使得矩阵用答案的 n 次方算出来
//
// Fn = F1 * A^n-1 => 快速幂求两个矩阵相乘

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long LL;

const int N = 3;
int n, m; 

// 一维矩阵乘二维
void mul(int c[], int a[], int b[][N])
{
    int tmp[N] = { 0 };             // 定义临时变量防止冲突, 因为不能边改边读
    for (int i = 0; i < N; ++ i )   // 枚举每个数, 二维乘一维
        for (int j = 0; j < N; ++ j )
            tmp[i] = (tmp[i] + (LL)a[j] * b[j][i]) % m;
    memcpy(c, tmp, sizeof tmp);     // 等于第一维向量 * 第二维向量的第 i 列
}

void mul(int c[][N], int a[][N], int b[][N])
{
    int tmp[N][N] = { 0 }; // 定义临时变量防止冲突, 因为不能边改边读
    for (int i = 0; i < N; ++ i )    // 二维 * 二维是三重循环
        for (int j = 0; j < N; ++ j )
            for (int k = 0; k < N; ++ k )
                tmp[i][j] = (tmp[i][j] + (LL)a[i][k] * b[k][j]) % m; // 第一个第 i 行 * 第二个的第 j 列
    memcpy(c, tmp, sizeof tmp);
}

int main()
{
    scanf("%d%d", &n, &m);

    int f1[3] = {1, 1, 1};  // fn, fn+1, sn
    int a[N][N] = {     // 矩阵 A
        {0, 1, 0}, 
        {1, 1, 1},
        {0, 0, 1}
    };

    n -- ;  // 求的是 f1 * k^n-1
    while (n)
    {
        if (n & 1) mul(f1, f1, a);  // res * a
        mul(a, a, a);    // a = a * a(每次将 a 倍增一下)
        n >>= 1; 
    }

    cout << f1[2] << endl;

    return 0;
}
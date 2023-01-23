#include <iostream>

using namespace std;
const int MAXN = 1003;

int main()
{
    int i, A[1005]={0}, B[1005]={0}, n, j;      
    // A[] 算的是加法, B[] 算的是乘法
    // 从 !2 开始算, 算完后直接和 A[] 数组累加
    // i-1 的累加和 i 的阶乘相加
    scanf("%d", &n);
    A[0] = B[0] = 1;

    for (i = 2; i <= n; i ++ )
    {
        for (j = 0; j < 100; j ++ )
            B[j] *= i;      // B 的每一位累乘上阶乘, 类似模板里的乘法

        for (j = 0; j < 100; j ++ )
            if (B[j] > 9)           // 如果这位 >= 10, 就将这位进行分解
            {
                B[j + 1] += B[j] / 10;
                B[j] %= 10;
            }

        for (j = 0; j < 100; j ++ )
        {
            A[j] += B[j];
            if (A[j] > 9) 
            {
                A[j + 1] += A[j]/10;
                A[j] %= 10;
            }
        }
    }
    // 最后倒着输出答案
    for (i = 100; i >=0 && A[i] ==0 ; i -- );
        for (j = i; j >=0 ; j -- ) 
            printf("%d", A[j]);
    return 0;
}
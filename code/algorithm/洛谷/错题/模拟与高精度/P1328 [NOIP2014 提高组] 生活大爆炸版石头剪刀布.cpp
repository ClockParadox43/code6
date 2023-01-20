#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int A[205], B[205];

// 错误原因: 25 行没有换, 下标取错了
// 输:-1, 赢:1, 平:0
// 0:剪刀, 1:石头, 2:布, 3:蜥蜴人, 4:斯波克

int rlue[5][5] = { {0, 0, 1, 1, 0}, {1, 0, 0, 1, 0}, {0, 1, 0, 0, 1}, {0, 0, 1, 0, 1}, {1, 1, 0, 0 ,0} };

int main()
{
    int n, a, b; scanf("%d%d%d", &n, &a, &b);
    for (int i = 0; i < a; ++i) scanf("%d", &A[i]);
    for (int i = 0; i < b; ++i) scanf("%d", &B[i]);

    // 当满足 A 的周期时, 长度不要超过 a, 所以就是 % a
    int Sa = 0, Sb = 0;
    for (int i = 0; i < n; ++i)
    {
        Sa += rlue[A[i % a]][B[i % b]];
        Sb += rlue[B[i % b]][A[i % a]];
    }

    cout << Sa << ' ' << Sb;
    return 0;
}

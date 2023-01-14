#include <iostream>
#include <cstring>

using namespace std;
const int MAXN = 1005;

int n = 5;
int a[MAXN] = {4, 2, 3, 1, 5};
int q[MAXN];
int dp[MAXN];


void solveI()
{
    int len = 0;

    // 处理边界, 为了保证 q[] 上小于 a[i] 的某个数字
    // 因为会在 q[] 上二分出某个小于 a[i] 的最大的值
    q[0] = -2e9;    
    // 枚举所有数, 找到对于当前长度最小的值
    for (int i = 0; i < n; ++ i)
    {
        int l = 0, r = len;
        while (l < r)
        {
            int m = (l + r + 1) >> 1;
            if (q[m] < a[i]) l = m;
            else r = m - 1; 
        }
        len = max(len, l + 1);
        q[l + 1] = a[i];
    }

    cout << len << endl;

}

void solveII()
{
    dp[0] = -2e8;
    for (int i = 0; i < n; ++ i)
        *lower_bound(dp, dp + n, a[i]) = a[i];  // 返回小于 a[i] 的最大的值的迭代器
    printf("%d\n", lower_bound(dp, dp + n, -2e8) - dp);
}

int main()
{
    // solveI();
    solveII();
    return 0;
}
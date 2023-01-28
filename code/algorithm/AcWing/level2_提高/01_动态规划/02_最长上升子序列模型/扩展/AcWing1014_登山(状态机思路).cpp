#include <iostream>

using namespace std;

const int N = 1010;

int n;
int a[N];
int f[N][2];

// 如果当前状态是 "上升状态", 则它下一个状态维持 "上升状态" 或者变成 "下降状态" 
// 而对于 "下降状态" 的状态, 下一个状态只能继续维持 "下降状态"
// 
// 状态表示 f[i,j]: 以第 i 个位置作为当前子序列的右端点, 且当前状态为 j
// 属性: 方案的子序列长度最大Max
int main()
{
    //input
    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> a[i];

    //dp
    for (int i = 1; i <= n; ++ i)
    {
        f[i][0] = f[i][1] = 1;
        for (int k = 1; k < i; ++ k)
        {
            if (a[k] < a[i]) f[i][0] = max(f[i][0], f[k][0] + 1);       // 前面小于当前, 上升状态
            if (a[k] > a[i]) f[i][1] = max(f[i][1], max(f[k][0], f[k][1]) + 1);  // 前面大于当前, 下降状态
        }
    }

    //find result from all final states
    int res = 0;
    for (int i = 1; i <= n; ++ i) res = max(res, max(f[i][0], f[i][1]));
    cout << res << endl;

    return 0;
}
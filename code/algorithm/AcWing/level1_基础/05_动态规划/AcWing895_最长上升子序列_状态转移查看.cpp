// 1) 在 a[i] > a[j] 的情况下 , 找到 f[i] < f[j] + 1 的数
// 2) 记录从 j 位置状态转移过来的路径, 此时的 g[i] 中存的就是它从谁那转移过来
// 3) 找到最长上升子序列的下标
// 4) 打印

// 7
// 3 1 2 1 8 5 6
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010, INF = 1e9;

int n;
// int a[N];
int f[N];
int g[N]; // 保存最长上升子序列, 存储每个状态是从哪个状态的下标转移过来的

// g[] 数组的值不会被覆盖掉, 因为上升子序列只会越来越长, 之前从哪转移过来是固定的
int main()
{
    // cin >> n;
    // for (int i = 0; i <= n; ++ i ) a[i] = -INF;

    // for (int i = 1; i <= n; ++ i ) cin >> a[i];

    n = 7;
    int a[8] = {0, 3, 1, 2, 1, 8, 5, 6};

    for (int i = 1; i <= n; ++ i ) 
    {
        g[i] = f[i] = 1;
        for (int j = 1; j < i; ++ j ) 
            if (a[j] < a[i])
                if (f[i] < f[j] + 1)     // 当前以 i 位置结尾的子序列长度 < 以 j 位置的子序列长度, 就从 j 位置转移过来  
                {                        // 这是在 i 位置值 > j 位置值的情况下
                    f[i] = f[j] + 1;
                    g[i] = j;            // 记录 f[i] 是从谁那转移过来的
                }
    } 

    // 求最长子序列下标
    int k = 1;
    for (int i = 1; i <= n; ++ i ) 
        if (f[k] < f[i]) k = i;
    
    cout << f[k] << endl;

    // 根据 g[] 可以知道 f[k] 是从哪个状态转移过来的
    // f[k] 表示的是以 k 结尾的最长子序列长度
    for (int i = 0, len = f[k]; i < len; ++ i ) 
    {
        cout << a[k] << ' ';
        k = g[k];
    }

    return 0;
}
// 公司的数量 -> 物品组
// 分配到的机器是固定的 -> 对于第i家公司不同的机器数量可以看做物品组内的物品
// 机器的总数量也是最大容积

#include <iostream>

using namespace std;

const int N = 11, M = 16;

int n, m;
int w[N][M];
int f[N][M];
int way[N];

int main()
{
    cin >> n >> m;
    // 依次枚举每个物品组
    for (int i = 1; i <= n; ++ i) 
        for (int j = 1; j <= m; ++ j)
            cin >> w[i][j];
    
    for (int i = 1; i <= n; ++ i)       // 枚举物品组
        for (int j = 0; j <= m; ++ j)   // 分配 j 台设备
        {
            f[i][j] = f[i - 1][j];
            for (int k = 0; k <= j; ++ k)   // 为第i组腾出j-k台设备的位置
                f[i][j] = max(f[i][j], f[i - 1][j - k] + w[i][k]);
        }                
    cout << f[n][m] << endl;
    // 终点f[n][m]
    int j = m;
    for (int i = n; i; -- i)
        for (int k = 0; k <= j; ++ k)
            if (f[i][j] == f[i - 1][j - k] + w[i][k])
            {
                way[i] = k;     // 第i家公司对应的k台机器
                j -= k;         // 减去k台机器
                break;
            }
    for (int i = 1; i <= n; ++ i) cout << i << ' ' << way[i] << endl;            
    return 0;
}   
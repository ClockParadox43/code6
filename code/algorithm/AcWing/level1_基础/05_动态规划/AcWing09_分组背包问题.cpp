
// 分组背包问题一般指 : 每组物品有若干个, 同一组物品最多只能选一个
// 
// 状态表示f[i,j]: 在不超过体积 j 的情况下, 从每组物品中选 1 个物品, 的最大价值是多少
//           属性: Max 
// 状态计算: 
//          1) 当前组不选择: f[i-1, j]
//          2) 当前第 i 组第 k 个物品选择: f[i-1, j-v[i,k]]+w[i,k]

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;

int n, m;
int v[N][N], w[N][N], s[N];           // 第 i 组物品第 j 个物品的体积/价值
int f[N][N];

int main()
{
    cin >> n >> m;

    for (int i = 1; i <= n; ++ i )              // n 组物品
    {                                       
        cin >> s[i];                            // 第 i 组物品有 s[i] 个
        for (int j = 0; j < s[i]; ++ j )           
            cin >> v[i][j] >> w[i][j];          // 第 i 组第 j 个物品的体积/价值
    } 

    for (int i = 1; i <= n; ++ i )
        for (int j = 0; j <= m; ++ j )
        {
            f[i][j] = f[i - 1][j];             // i-1 最先拿到的是 0, 所以最差情况就是放不下物品
            for (int k = 0; k < s[i]; ++ k )   // 枚举第 i 组的所有物品 
                if (j >= v[i][k]) f[i][j] = max(f[i][j], f[i - 1][j - v[i][k]] + w[i][k]);   

                // 因为从当前组选一个物品, 第 3 层循环在枚举当前组物品
                // 所以是 f[i-1][j - v[i,j-k]], 每次减去的都是当前组的   
        }              
    
    /*
     for (int i = 1; i <= n; ++ i )
        for (int j = 0; j <= m; ++ j )
            for (int k = 0; k < s[i]; ++ k ) 
            {
                f[i][j] = f[i - 1][j];  
                if (j >= v[i][k]) f[i][j] = max(f[i][j], f[i - 1][j - v[i][k]] + w[i][k]);   
            }    
           
     错误原因: 因为 f[i - 1][j] 表示的是当前第 i 组物品不选择的情况
               如果这段放到第 3 层循环意义就变成当前第 i 组物品第 k 个物品不选的情况
               (主要会重复更新答案, 之前的答案会在没有被 max 判定过的情况下被更新)
    */
    cout << f[n][m] << endl;
    return 0;
}
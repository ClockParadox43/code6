// 预处理: 判断合并列的状态是否合法
//         - 将相邻的两列进行位运算, 即 "按位或"
// 如果和并列的某行是 1 表示横放, 是 0 表示竖放
// 如果合并列不存在连续奇数个 0, 即为合法状态
// 该题是状态与状态之间的转移

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 12, M = 1 << N;
typedef long long LL;

LL f[N][M];
bool st[M];     

// st 数组状态打印
void print_st(bool* st, int n)
{
    for (int i = 0; i < n; ++ i ) printf("st[%d] = %d\n", i, st[i]);
    printf("\n");
}

void print_binary(int num)
{
    for (int i = 31; i >= 0; -- i )
        printf("%d ", num >> i & 1);
    printf("\n");
}

int main()
{
    int n = 3, m = 3; 
    memset(f, 0, sizeof f);
    // 该循环对所有的状态进行预处理
    // 预处理所有状态是否存在连续奇数个 0
    for (int i = 0; i < 1 << n; ++ i)
    {
        st[i] = true;       // 假设当前是合法状态
        int cnt =  0;       // 记录合并列中 0 的个数 
        
        // 从第 0 行枚举到第 n 行, 枚举 i 的状态是 1 之前的 0 有几个
        for (int j = 0; j < n; ++ j)
        {
            // 总结:
            // 总的来讲第一个 if 是判断 1 前 0 的个数, 第二个 if 判断 1 前 0 的个数是否为奇数如果是奇数直接 break
            // 第三个 if 的含义是当所有 1 前 0 的个数为偶数满足那么就检验所有 0 即剩下 0 的个数是不是偶数 
            if (i >> j & 1)     // 将当前状态右移 j 位
            {                   
                if (cnt & 1)    // 如果是 1, 就判断是否存在连续奇数个 0 (因为不能碰到连续奇数个 0, 每碰到一个 1 就判断一下)
                {
                    st[i] = false; // 存在的话该状态就置为 false
                    break;
                }
            }else ++ cnt ;
        }
        if (cnt & 1) st[i] = false;
        else 
        {
            // printf("%d : ", i); 
            // print_binary(i);        // 否则就将合法的具体状态打印出来
        } 
    }
    
    // print_st(st, 1 << n);        // 打印 st 数组

    // 动态规划
    f[0][0] = 1;                                   // 第 0 列不横放是一种合法方案
    for (int i = 1; i <= m; ++ i)                  // 枚举列
        for (int j = 0; j < 1 << n; ++ j)          // 枚举第 i 列的状态   -> (j 和 k 都是状态)
            for (int k = 0; k < 1 << n; ++ k)      // 枚举第 i-1 列的状态 
                if ((j & k) == 0 && st[j | k])     // 两列状态不矛盾的情况 (已经预处理 st 数组的所有状态)
                {
                    f[i][j] += f[i - 1][k];
                    // printf("f[%d,%d] = %d -> f[%d,%d] = %d\n", i-1, k, f[i-1][k], i, j, f[i][j]);
                }
                
    printf("%lld\n", f[m][0]);
    
    // f[i,j] 代表第 i 列状为 j 时
    for (int i = 1; i <= m; ++ i )
        for (int j = 0; j <= 1 << n; ++ j ) 
            printf("f[%d,%d] = %d\n", i, j, f[i][j]);
    return 0;
}
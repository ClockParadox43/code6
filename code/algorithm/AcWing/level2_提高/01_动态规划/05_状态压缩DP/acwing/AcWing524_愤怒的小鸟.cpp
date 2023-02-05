// 重复覆盖问题模型:给定一个01矩阵, 选择尽量少的行, 让每一列至少包含一个1
// 精确覆盖问题模型:最少选择多少行, 使得每一列, 至少选择1个1, 例:数独, 8皇后
// 该问题给定多个点, 用尽量少的抛物线对每个点进行覆盖, 每个点必须经过一次, 可以重复经过
//      - 属于重复覆盖问题
// 最优解是dancing links
// 思路: 用状压优化暴搜
// state: 存储哪些列已经被覆盖掉了
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define fs first
#define sc second

using namespace std;

typedef pair<double, double> pdd;
const int N = 20, M = 1 << N;
const double eps = 1e-8;

int n, m;
pdd ver[N];
int path[N][N]; // path[i][j] 表示第i个点和第j个点构成的抛物线能覆盖的点的状态
int f[M];       // 当前击败状态i上的小猪所需要的最少的小鸟 

int cmp_if(double a, double b)  //浮点数比较
{
    if (fabs(a - b) < eps) return 0;
    if (a > b) return 1;
    return -1;
}

// 预处理所有抛物线
void init_path()
{
    memset(path, 0, sizeof path);
    for (int i = 0; i < n; ++ i)
    {
        path[i][i] = 1 << i;    // 单独生成一条只经过(0,0)和(x,y)的抛物线
        for (int j = 0; j < n; ++ j)
        {
            double x1 = ver[i].fs, y1 = ver[i].sc;
            double x2 = ver[j].fs, y2 = ver[j].sc; 
            if (!cmp_if(x1, x2)) continue; // 抛物线上不存在斜率为无限大的切线
            double a = (y1 / x1 - y2 / x2) / (x1 - x2); // 给定(x,y), 求出a, b, 确定一条抛物线
            double b = (y1 / x1) - a * x1;
            if (cmp_if(a, 0.0) >= 0) continue; // a < 0(不是开口向下的抛物线)
            // 参数 a, b 的抛物线已生成, 计算path[i][j]的能覆盖的点的状态
            for (int k = 0; k < n; ++ k)
            {
                double x = ver[k].fs, y = ver[k].sc;
                // y = ax^2 + bx, 如果 y 在这条抛物线上, 就加入状态
                if (!cmp_if(y, a * x * x + b * x)) path[i][j] += 1 << k;
            }
        }
    }
}

int main()
{
    int T; cin >> T;
    
    while (T -- )
    {
        cin >> n >> m;    // n:点的数量, m
        for (int i = 0; i < n; ++ i) 
            cin >> ver[i].fs >> ver[i].sc; // 将点读进来
        init_path();
        
        // dp
        memset(f, 0x3f, sizeof f);
        f[0] = 0;   // 0这个状态没有抛物线
        // n 个点就有 2^n 条抛物线, 枚举所有状态, 全部是1的转态不用更新, 所以cur_st+1
        for (int cur_st = 0; cur_st + 1 < 1 << n; ++ cur_st)
        {
            // 找到一个任何没有被覆盖掉的点
            int t = -1;
            for (int i = 0; i < n; ++ i)    // 找到st中一个没有被覆盖掉点的标号
                if(!(cur_st >> i & 1)) { t = i; break; }        

            // 如果st中存在没有被覆盖掉的标记, 就转移过来进行对比 

            // 所有能覆盖掉 t 的抛物线就是 path[t,j]中存的
            // f[st] 表示当前已经覆盖的列是i时的最小行数
            // 转移时随便找到当前未被覆盖的某一列 t，然后枚举所有包含t的行j来选择即可
            for (int i = 0; i < n; ++ i)
            {
                int ne_st = path[t][i] | cur_st;
                f[ne_st] = min(f[ne_st], f[cur_st] + 1);
            }
        }
        cout << f[(1 << n) - 1] << endl;
    }

    return 0;
}
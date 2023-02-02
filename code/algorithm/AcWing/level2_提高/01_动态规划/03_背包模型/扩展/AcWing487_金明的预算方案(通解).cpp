// 不用STL, 直接分组背包, 拆出价值w和价格V就可以了
#include <iostream>

using namespace std;

const int N = 62, M = 32010;

int n, m;
int f[N][M];
int w[N][M];    // 价值是v*p, 我们要使得vp最大
int v[N][M];    
int cnt[N];     // 和第i个主件搭配的附件的组合的数量

int main()
{
    cin >> m >> n;
    for (int i = 1; i <= n; ++ i)
    {
        int vl, p, q; cin >> vl >> p >> q;  // vl:价格, p:重要度, q:主(q=0)/附件(q>0):所数主件的编号
        if (!q)  // 如果是主件
        {
            w[i][ ++ cnt[i]] = vl * p;      // 第i个主件搭配的附件的价值 (将和主件搭配的附件看做组呢物品, 所以cnt要加1)
            v[i][cnt[i]] = vl;              // 第i个主件对应的附件v(必要程度, 主件对应的自己的必要程度) 
        }
        else
        {
            // 如果是附件
            if (cnt[q] == 1)    // 因为此时的主件只有1个所以只能多出一种方案
            {
                w[q][ ++ cnt[q]] = vl * p + w[q][1];    // 对应主见的方案加1并且vp累加上主件的对应的价值
                v[q][cnt[q]]  = vl + v[q][1];           // 附件的v累加上对应主件的v
            }
            else            // 一种方案以上的情况
            {
                w[q][ ++ cnt[q]] = vl * p + w[q][1];    
                v[q][cnt[q]] = vl + v[q][1];
                w[q][ ++ cnt[q]] = vl * p + w[q][2];
                v[q][cnt[q]] = vl + v[q][2];
            }
        }
    }
    
   
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j <= m; ++ j)
        {
            f[i][j] = f[i - 1][j];
            for (int k = 1; k <= cnt[i]; ++ k)
                if (j >= v[i][k])
                    f[i][j] = max(f[i][j], f[i - 1][j - v[i][k]] + w[i][k]);
        }
    cout << f[n][m] << endl;
    return 0;
}
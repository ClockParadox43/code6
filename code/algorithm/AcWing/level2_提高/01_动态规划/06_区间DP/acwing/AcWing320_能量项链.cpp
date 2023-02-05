#include <iostream>
#include <cstring>

using namespace std;
const int N = 204;

int n;
int a[N];
int f[N][N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> a[i];
        a[i + n] = a[i];
    }
    // f[l][r]:当长度为n的时候求 l, r 的最大值
    // 最后一步:将长度为3的区间合并成长度为2的区间
    // 断开链后会多一个点, 所以+1
    for (int len = 3; len <= n + 1; ++ len)
        for (int l = 1; l + len - 1 <= 2 * n; ++ l)
        {
            int r = l + len - 1;
            // k作为隔板, 是需要合并的两个珠子之间的公共值(前一个的尾, 后一个的头) 
            // 填充f的顺序保证了这个子集已经计算过了
            // 闫总的写法好像是不断填充对角元素
            // 也能保证每个元素在计算时其左侧和下侧的元素都已经被计算. 代码可能更容易记一点
            for (int k = l + 1; k < r; ++ k)
                f[l][r] = max(f[l][r], f[l][k] + f[k][r] + a[l] * a[k] * a[r]);
        }
    
    // 硬核理解k=l+1:每次len+1时, 之前的子集已经处理过了
    // 之前的子集的值累加上差集, 中间有一个1的间隔
    int ans = 0;
    for (int i = 1; i <= n; ++ i)
        ans = max(ans, f[i][i + n]);    
    cout << ans << endl;
    
    return 0;
}

// 从2开始的写法
/*
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) scanf("%d", &w[i]), w[n + i] = w[i];
    memset(f, -0x3f, sizeof f); //本题可以不用初始化，因为不存在负数的状态值，因此0就是最小的
    for (int len = 2; len <= n + 1; ++ len)
        for (int l = 1, r; (r = l + len - 1) <= n << 1; ++ l)
            if (len == 2) f[l][r] = 0; //初始化初始状态
            else
                for (int k = l + 1; k < r; ++ k)
                    f[l][r] = max(f[l][r], f[l][k] + f[k][r] + w[l] * w[k] * w[r]);
    int res = 0;
    for (int l = 1; l <= n; ++ l) res = max(res, f[l][l + n]);
    printf("%d\n", res);
    return 0;
}
*/
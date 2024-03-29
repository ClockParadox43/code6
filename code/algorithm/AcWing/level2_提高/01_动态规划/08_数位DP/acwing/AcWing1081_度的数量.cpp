// 题目要求再[X,Y]中, 找到K个互不相等的B的次幂之和
// 例: 17 = 2^4 + 2^0
//     18 = 2^4 + 2^1
//     20 = 2^4 + 2^2
// 所以我们可以将问题转化成[X,Y]中表示成B进制, 其中包含2个1的数的个数
// 15: 0111
// 16: 1000
// 17: 1001
// 18: 1010
// 19: 1011
// 20: 1100
// K个互不相等:代表B的整数次幂只能由k个组成, 所以就是2个1 
// 例: 17=2^4+2^1转换成2进制就是10010, 如果是三进制就是 10 = 3^2+3^0 = 101, 
//     因为把K进制转化成10进制就是a0*k^0 + a1*k^1 + .... + an*k^n，所以能转化成0和1的原因就是, 
//     n能够表示成k个系数为1的b的次幂之和, 然后, n的b进制中恰好有k个1且余位必须是0
//     
//     B进制其余的数哪去了?
//     题目要求的是B的整数次幂之和, 还必须是K个, 也就是说多出>1的数都是不合法的数, 
//     符合条件的就是B进制有K个1且余位为0的数, 并不是没有, 而是那些数不合法
//
// 分析:
//      利用前缀和的思想, 想要求出[X,Y]中满足性质的数的个数就要求出[0~Y]中所有满足性质的数的个数
//      然后再用 f(Y) - f(X-1) 就能求出这个区间中满足性质的数的个数
//
//      用树的思想进行分类讨论
#include <iostream>
#include <vector>

using namespace std;

const int N = 35;

int l, r, B, K;
int f[N][N];    // f[a,b]:从a个数中选b个数的方案数

// 预处理组合数:从i个数中选择j个数
void init()
{
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j <= i; ++ j)
            if (!j) f[i][j] = 1;        // 从i个数中选0个数的方案数
            else f[i][j] = f[i - 1][j] + f[i - 1][j - 1];   
}

// 从0~n中选择满足条件的数的方案数
int dp(int n)
{
    if (!n) return 0;
    
    vector<int> nums;   
    // 将n的每一位单独拿出
    while (n) nums.push_back(n % B), n /= B;

    // last 在数位dp中存储的数: 右边分支往下走的时候保存前面的信息
    // 遍历当前位的时候, 记录之前那些已经占用多少个1, 那么当前还能用1的个数就是k-last个1
    int res = 0, last = 0;  
    // 因为最开始拿出的是低位, 想要枚举到高位就得反着来
    // 步骤:
    //  从最高位开始枚举
    //  左边分支:选择0~an-1中的数填在当前位, 右边分支:选择an填在当前位
    //        ps:本题只能填0或者1
    for (int i = nums.size() - 1; i >= 0; -- i)
    {
        int x = nums[i]; 

        // 只有在x>1的时候, 才能有左树的 左右分支可以讨论
        // 如果x=0, 那么左边的分支就不存在
        if (x) 
        {
            // 当前位填0:
            res += f[i][K - last];

            // 只有当前为>1, 后面填什么都不会超过, 填1的话总共的填1的个数就是last+1
            // 因为只有0和1所以方案都枚举完了, break
            if (x > 1)
            {
                if (K - last - 1 >= 0) 
                    res += f[i][K - last - 1];   // 第i位填1,剩下的i-1位填剩余个1
                break;  // 方案数已经枚举完毕,无须再进行讨论
            }
            else 
            {
                // 左边分支枚举完了, x=1, 走了右边分支, 固定住当前的1, 进一位, 下一位可用的1少1
                // 开始处理树的下一个分支
                last ++ ; 
                if (last > K) break;
            }
        }
        // 以上代码处理完了该树的左侧分支, 开始处理该树的右侧分支
        if (!i && K == last) ++ res;
    }
    return res;
}

int main()
{
    init();
    cin >> l >> r >> K >> B;
    cout << dp(r) - dp(l - 1) << endl;
    return 0;
}
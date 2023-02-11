// 不能包含7
//  1.整数中某一位是7
//  2.整数的每一位加起来的和是7的整数倍
//  3.整数是7的倍数
// 求一定区级和7无关的整数的平方
//
// 转化:
// 数位DP:
//  1.每一位不含7
//    设:已经固定的 an-1,an-2,..a0这类数为x
//       小于 "当前最高位的数" 为k
//  2.[(各位数字之和)+ x + k] % 7 != 0
//  3.[(后面的数) + (x * 10^n-i) + (k * 10^n-i-1)] % 7 != 0
// 
// 详细见图片
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
const ll N = 20, P = 1e9 + 7;

// 有(jA1)^2 +...+ (jAt)^2 
// s0:表示合法数的个数, s1:A的和, s2:A的平方和
struct F
{
    ll s0, s1, s2;  
}f[N][10][7][7];
ll power7[N], power9[N];    // 10^i%7, 10^i%p

ll mod(ll x, ll y) { return (x % y + y) % y; }

void init()
{
    // 初始长度为1的情况, 对于第i位来说是i-1位
    for (int i = 0; i < 10; ++ i)
        if (i != 7)
        {
            auto& v = f[1][i][i % 7][i % 7];        // 当前1位数, 最高位是i, 记录该数%7的余数, 各位数字之和%7的余数
            v.s0 ++ , v.s1 += i, v.s2 += i * i;     // 记录该格子元素的信息
        }

    ll power = 10;
    for (int i = 2; i < N; ++ i, power *= 10)
        for (int j = 0; j <= 9; ++ j)
        {
            if (j == 7) continue;   // 最高位不能为7

            for (int a = 0; a < 7; ++ a)        // 第i位,该数%7的余数为a
                for (int b = 0; b < 7; ++ b)    // 第i位,各位数字之和%7的余数为b
                    for (int k = 0; k <= 9; ++ k) // 枚举决策, f[i,j,a,b]来自f[i-1,k,y,x]
                    {
                        if (k == 7) continue;   // 第i-1位的最高位不能是7
                        // A代表i-1位不同的数

                        // v1:当前状态, 对于k这层循环来说,v1是一个常量 v2:v1所以依赖的状态
                        // 第i位数字依赖第i-1位数字, 求第i-1位数:用第i位数的最高位的数字*10^i-1, 就是第i-1位数
                        // 各位数字之和:减去第i位数的最高位的数, 就是i-1位数的各位数字之和
                        auto &v1 = f[i][j][a][b], &v2 = f[i - 1][k][mod(a - j * mod(power, 7), 7)][mod(b - j, 7)];
                        v1.s0 = mod(v1.s0 + v2.s0, P);  // 符合条件的数的个数的累加和
                        
                        // t * (j*10^i-1) + (A1+..At) -> A的一次方
                        // ({v1.s1 + j * power * v2.s0} + v2.s1) % P, 优先看中括号内的
                        v1.s1 = mod(v1.s1 + j * (power % P) % P * v2.s0 % P + v2.s1 , P);
                        
                        // 我们要做的就是, 将最高位为j的数加上i-1位数的平方进行累加
                        // ps:i-1位的数有各种组合
                        // 
                        // 这里的本质其实就是将式子: (jA1)^2 + (jA2)^2 + ... + (jAt)^2 -> A代表i-1位
                        // 乘开后进行归纳, 变成了大号的平方和: 设 a =  j * 10^i-1, b = A1+..+At
                        // t(j * 10^i-1)^2 + 2(j * 10^i-1)(A1+..+At) + (A1^2 +...At^2)
                        // 两个式子等价

                        // ({j * j * (power % P) % P * (power % P) % P * v2.s0} +  // v2.s0:t
                        //  {2 * j * (power % P) % P * v2.s1 % P +} v2.s1:之前的和
                        //  v2.s2(之前的平方和)
                        // )
                        v1.s2 = mod(v1.s2 + 
                                    v2.s0 * j % P * (power % P) % P * j % P * (power % P) % P +  // 平方和的第一项 t*(j*10^i-1)^2
                                    2 * j % P * (power % P) % P * v2.s1 % P +  // 2倍的当前位, 2倍的i-1位一次项
                                    v2.s2 , P); // 平方和的第三项sum(A1^2..At^2), i-1位的数的平方和
                    }
        }

    // 预处理10^i%7的结果和10^i%P的结果
    power7[0] = power9[0] = 1;
    for (int i = 1; i < N; ++ i)
    {
        power7[i] = power7[i - 1] * 10 % 7;
        power9[i] = power9[i - 1] * 10 % P;
    }
}

// 求出i位, 且最高位是j, 且本身模7不等于a, 且各位数之和模7不等b的集合
// 因为预处理的f[i,j,a,b]是本身模7等于a, 且各位数之和模7等于b的集合, 因此需要两趟for循环来实现
F get(int i, int j, int a, int b)
{
   // 因为f[i][j][a][b]是本身模7等于a，且各位数之和模7等于b的, 所以我们需要找出符合条件的集合
    ll s0 = 0, s1 = 0, s2 = 0;
    for (int x = 0; x < 7; ++ x)
        for (int y = 0; y < 7; ++ y)
        {
            if (x == a || y == b) continue;
            auto v = f[i][j][x][y];
            s0 = mod(s0 + v.s0, P);     // 符合条件的数的个数
            s1 = mod(s1 + v.s1, P);     // 符合条件的数的1次方的和
            s2 = mod(s2 + v.s2, P);     // 符合条件的数的平方的和
        }
    return {s0, s1, s2};
}

ll dp(ll n)
{
    if (!n) return 0;
    ll backup_n = n % P;        // 备份一个n
    vector<int> nums;
    while (n) nums.push_back(n % 10), n /= 10;

    ll res = 0;
    ll last_a = 0, last_b = 0;  // last_a 表示是前缀本身的值, last_b表示前缀各位数之和
    for (int i = nums.size() - 1; i >= 0; -- i)
    {
        int x = nums[i];
        for (int j = 0; j < x; ++ j)
        {
            if (j == 7) continue;
            
        
            int a = mod(-last_a * power7[i + 1], 7), b = mod(-last_b, 7); 
            // 我们需要将符合条件的数筛出来
            // 求得本身模7不等于a, 并且各位数之和模7不等b的集合
            // 此时就可以使用预处理出来的结构体
            auto v = get(i + 1, j, a, b);     
            res = mod(res + 
                    (last_a % P) * (last_a % P) % P * (power9[i + 1] % P) % P * (power9[i + 1] % P) % P * v.s0 % P + 
                    2 * (last_a % P) * (power9[i + 1] % P) % P * v.s1 % P + 
                    v.s2 , P);
        }
        if (x == 7) break;
        last_a = last_a * 10 + x;
        last_b += x;

        // 判断n本身
        if (!i && last_a % 7 && last_b % 7) res = mod(res + backup_n * backup_n, P);
    }
    return res;
}

int main()
{
    init();
    int T; cin >> T;
    while (T -- )
    {
        ll l, r; cin >> l >> r;
        cout << mod(dp(r) - dp(l - 1), P) << endl;
    }
    return 0;
}
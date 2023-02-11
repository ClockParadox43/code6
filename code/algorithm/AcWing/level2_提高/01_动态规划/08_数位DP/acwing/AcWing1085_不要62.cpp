#include <iostream>
#include <vector>

using namespace std;
const int N = 35;

int l, r;
int f[N][10];

void init()
{
    // f[i][j]:最高位是j, 一共有i位, 不含4和62的数的个数
    for (int i = 0; i <= 9; ++ i) f[1][i] = 1;
    for (int i = 2; i < N; ++ i)        
        for (int j = 0; j <= 9; ++ j)   // 枚举当前最高位
        {
            if (j == 4) continue;
            for (int k = 0; k <= 9; ++ k)       // 枚举决策
            {
                if (k == 4 || j == 6 && k == 2) continue;
                f[i][j] += f[i - 1][k];         // f[i-1,k]第i-1位, 最高位为k
            }
        }
}

int dp(int n)
{
    if (!n) return 1;
    vector<int> nums;
    while (n) nums.push_back(n % 10), n /= 10;  // 将每一位放入nums
    
    int res = 0, last = 0;      // last:表示上一位
    
    for (int i = nums.size() - 1; i >= 0; -- i) // 从最高位开始枚举
    {
        int x = nums[i];                   // 最高位的数为x
        for (int j = 0; j < x; ++ j)       // 枚举次高位, 后面的位随便填(因为这样不会超过上限)
        {
            if (j == 4 || last == 6 && j == 2) continue;
            res += f[i + 1][j];   // 当前位为i, 最高位为j, 后面的数随便填的符合条件的数的个数, 下标为i, 就有i+1位
        }                         // 如果第2位最高位是4, 那就是40, 累加上<40所有符合条件的数
        
        if (x == 4 || last == 6 && x == 2) break;   // 因为是从最高位开始累加, 之前的数已经加完了, 可以直接break
        last = x;
        if (!i) ++ res; // 来到最后一位数字时还符合条件
    }
    return res;
}

int main()
{
    init();
    while (cin >> l >> r, l || r) 
        cout << dp(r) - dp(l - 1) << endl;
    return 0;
}
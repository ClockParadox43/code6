// 给定两个整数 a 和 b, 求 a 和 b 之间的所有数字中 0∼9 的出现次数 
// 因为求 1~n 中 x 出现的次数, count(n, x)  
// 那么求 a~b 中 x 出现的次数就是, count(b, x) - count(a-1, x) 
// 
// 思路: 
// abcdefg, 1 在每一位上出现的次数累加起来就是 1 在整个 1~n 中出现的次数
// 例: 想求出 1 在第 4 位上出现的次数, 也就是求 1 <= xxx1yyy <= abcdefg
//     1) xxx = 000~abc-1, 那么后三位 "yyy" 的值可以随便取, 
//        yyy = 000~999, 也就是 abc * 1000 种选法 
//        (000~999 有 1000 种数字, abc 每改变自己一位就能得到 1000 个数)
//     2) xxx = abc
//         - 2.1) d < 1, abc1yyy > abc0defg, 0
//         - 2.2) d = 1, yyy = 000~efg (abc 已经到达上限了, 后三位就不能超过上限), efg+1
//         - 2.3) d > 1, yyy = 000~999, 1000
// 
// 注意此处的 d 指的是 acbcdefg 的 d, 而非 xxx1yyy 的 1
// 这些情况代表的是一个区间可以取到的数
// 然后 abc * 1000, 判断哪种情况再累加上对应方案数, 求出 1 在任意一位出现的次数, 
// 再将每一位出现的次数累加起来, 就是 1 在 a~b 中出现的次数
//
// 前导 0 的情况:
//      当 x = 0 的时候 (2) 的所有情况是不用考虑的, 因为没有前导 0 的问题
//      主要 (1) 有前导 0 情况, 如果 d = 0, 那么 abc 不能取 0, 0000x 不是一个合法的表示
//      所以枚举的时候会从 1 开始枚举
// 
// 时间复杂度: 枚举每个数字, 两个区间分别算一次, 最多 8 位, 预处理(10*2*8*10 = 1600)  

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 求 abc
int get(vector<int> num, int l, int r)          
{
    int res = 0;
    for (int i = l; i >= r; -- i ) res = res * 10 + num[i];
    return res; 
}

// 求 10^i
int power10(int x)
{
    int res = 1;
    while (x -- ) res *= 10;
    return res;
}

// 统计 1~n 中, x 出现的次数
int count(int n, int x)
{
    if (!n) return 0;           // 当 n = 0, 没有数, 返回 0 

    vector<int> num;           
    while (n)                    // 将 n 中出现的每一位数字统计入 num 
    {
        num.push_back(n % 10);
        n /= 10;
    }
    
    n = num.size();     // n = num 的位数

    int res = 0;
    
    // i = n - 1 - !x : 当 x = 0 时, 应该从第 2 位开始枚举 
    for (int i = n - 1 - !x; i >= 0; -- i )  // 从最高位开始枚举
    {
        // 分 4 种情况
        // 1) 当枚举最高位的时候, (1) 其实是不存在的
        //    枚举最高位时, 最前面相当于 0, 枚举 0 ~ -1 是不存在的 
        //    所以 (1) 只有当 i < n-1 时才能存在
        if (i < n - 1) 
        {
            // 累加上当前枚举到的数字, 前面那几位的数字 * 10^i(正好到 d 的那位)
            res += get(num, n - 1, i + 1) * power10(i);

            // 特殊情况 x = 0 时, 该位要取 1, 也就是说要少一个数 
            if (!x) res -= power10(i);                      
        }         

        // 2.1) d 后面那些数字 + 1 
        // 2.2) 后面的数字 * 10^i
        if (num[i] == x) res += get(num, i - 1, 0) + 1;
        else if (num[i] > x) res += power10(i);
    }
    
    return res;
}

int main()
{
    int a, b;
    while (cin >> a >> b, a || b)
    {
        if (a > b) swap(a, b);

        // 统计每个数字出现的次数
        for (int i = 0; i < 10; ++ i ) 
            cout << count(b, i) - count(a - 1, i) << ' ';
        cout << endl;
    }
    return 0;
}